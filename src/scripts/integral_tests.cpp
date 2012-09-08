#include <cstdio>
#include <vector>
#include <string>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <curl/curl.h>

const int MAX_BUFFOR_LENGTH = 50000;
const int LIMIT_FOR_INT = 100;
const int NUMBER_OF_ITERATIONS = 18000;
const int DELETES_MODULO = 1000;

char buffor[MAX_BUFFOR_LENGTH];

enum LocalTypes {
    STRING, INT, DOUBLE
};

std::string get_type_name(LocalTypes type)
{
    switch(type) {
    case STRING:
        return "string";
    case INT:
        return "int";
    case DOUBLE:
        return "double";
    default:
        return "UNKNOWN_TYPE";
    }
}

std::string get_random(LocalTypes type)
{
    if (type == INT) return boost::lexical_cast<std::string>(rand() % LIMIT_FOR_INT);
    if (type == DOUBLE) return boost::lexical_cast<std::string>(double(rand() % 201 - 100) / (rand() % 43 + 1));

    int length = 1 + rand() % 2 + (rand() % 2) * 15;
    std::string res = "";
    for(int i=0; i<length; i++) {
        res += rand() % 26 + 'A';
    }
    return res;

}

struct TableDef {
    std::string table_name;
    std::vector<std::string> props;
    std::vector<LocalTypes> types;

    TableDef(int string_fields, int double_fields, int int_fields) {
        add_fields(INT, int_fields + 1);
        add_fields(STRING, string_fields);
        add_fields(DOUBLE, double_fields);
        table_name = "test_" + boost::lexical_cast<std::string>(rand() % 1000000);
    }

    void add_fields(LocalTypes type, int count) {
        for(int i=0; i<count; i++) {
            props.push_back(get_type_name(type) + "_" + boost::lexical_cast<std::string>(i));
            types.push_back(type);
        }
    }
};

struct Command {
    std::string command_name;
    std::string table;
    std::vector<std::string> props;
    std::vector<std::string> values;

    std::string to_string() {
        std::string result;
        sprintf(buffor, "/%s/%s/?", command_name.c_str(), table.c_str());
        result += buffor;
        for(std::size_t i=0; i<props.size(); i++) {
            if (i) result +='&';
            sprintf(buffor, "%s=%s",props[i].c_str(), values[i].c_str());
            result += buffor;
        }
        result += "\n";
        return result;
    }

    void init(const std::string& cmd, const TableDef& t) {
        command_name = cmd;
        table = t.table_name;
        props.clear();
        values.clear();
    }

    void create_insert(const TableDef& t, int id) {
        init("insert", t);
        for(std::size_t i=0; i<t.props.size(); i++) {
            props.push_back(t.props[i]);
            values.push_back(i == 0 ? boost::lexical_cast<std::string>(id) : get_random(t.types[i]));
        }
    }

    void create_delete(const TableDef& t) {
        init("delete", t);
        generate_query(t);
    }

    void create_search(const TableDef& t) {
        init("search", t);
        generate_query(t);

        int modulo;

        modulo = 30;
        if (rand() % 100 == 0) modulo = 1000000;
        values.push_back(boost::lexical_cast<std::string>(rand() % modulo));
        props.push_back("OFFSET");

        modulo = 30;
        if (rand() % 100 == 0) modulo = 1000000;
        values.push_back(boost::lexical_cast<std::string>(rand() % modulo));
        props.push_back("LIMIT");

        props.push_back("ORDER_BY");
        if (rand() % 2 == 0) values.push_back("int_0");
        else values.push_back("-int_0");
    }

    void create_table_command(const TableDef& t) {
        init("create_table", t);
        for(std::size_t i=0; i<t.props.size(); i++) {
            props.push_back(t.props[i]);
            values.push_back(get_type_name(t.types[i]));
        }
    }

    std::string print_drop(const TableDef& t) {
        sprintf(buffor, "/drop_table/%s\n", t.table_name.c_str());
        return std::string(buffor);
    }

    std::string wrap(LocalTypes type, std::string prop_name) {
        std::string wrap;
        if (type == STRING && rand() % 2 == 0) {
            if (rand() % 3 == 0) wrap = "PREFIX";
            else if (rand() % 2 == 0) wrap = "SUBSTRING";
        } else {
            if (rand() % 5 == 0) wrap = "GREATER";
            else if (rand() % 4 == 0) wrap = "GREATER_OR_EQUAL";
            else if (rand() % 3 == 0) wrap = "SMALLER";
            else if (rand() % 2 == 0) wrap = "SMALLER_OR_EQUAL";
        }
        if (wrap.size() < 2) {
            return prop_name;
        } else return wrap + "(" + prop_name + ")";
    }

    void generate_query(const TableDef& t) {
        for(std::size_t i=0; i<t.props.size(); i++) {
            if (rand() % 2 == 0) {
                props.push_back(wrap(t.types[i], t.props[i]));
                values.push_back(get_random(t.types[i]));
            }
        }
    }
};

void send(std::string url)
{
    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_perform(curl);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage ./prog host port\n";
        return 0;
    }

    std::string host(argv[1]);
    std::string port(argv[2]);

    std::string prefix = host + ":" + port;



    boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();
    boost::posix_time::ptime t1 = boost::posix_time::microsec_clock::local_time();
    srand((t1 - t2).total_nanoseconds());

    TableDef table(2, 2, 2);
    srand(57);

    Command c;
    send(prefix + c.print_drop(table));

    c.create_table_command(table);
    send(prefix + c.to_string());

    for(int i=0; i<NUMBER_OF_ITERATIONS; i++) {
        if (i % 1000 == 0) std::cerr << "DONE " << i << " COMMANDS IN " << table.table_name << std::endl;
        if (rand() % DELETES_MODULO == 1) c.create_delete(table);
        else if (rand() % 2 == 1) c.create_insert(table, i);
        else c.create_search(table);

        send(prefix + c.to_string());
    }
}
