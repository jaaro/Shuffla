CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-O2 -Wall -std=c++0x -c
LDFLAGS=-O2
LDLIBS=-lcurl -lboost_thread -lboost_system

SRCS_SHUFFLA=main.cpp src/server/http/reply.cpp src/server/http/connection.cpp src/server/http/request_handler.cpp src/server/http/mime_types.cpp src/server/http/http_server.cpp src/server/http/io_service_pool.cpp src/server/http/request_parser.cpp src/server/http/server.cpp src/server/query_dispatcher.cpp src/server/server.cpp src/engine/search_engine.cpp src/engine/search_result/results/search_results.cpp src/engine/search_result/string/search_result_string.cpp src/engine/search_result/search_result.cpp src/engine/search_result/errors/search_result_error.cpp src/engine/table/table.cpp src/engine/table/table_definition.cpp src/engine/query/query.cpp src/engine/query/query_create.cpp src/engine/query/delete/query_delete.cpp src/engine/query/drop_table/query_drop_table.cpp src/engine/query/create_table/query_create_table.cpp src/engine/query/search/functions/search_function_with_prefix.cpp src/engine/query/search/functions/search_function.cpp src/engine/query/search/functions/search_function_substring.cpp src/engine/query/search/functions/search_function_greater_or_equal.cpp src/engine/query/search/functions/search_function_greater.cpp src/engine/query/search/functions/search_function_equal.cpp src/engine/query/search/functions/search_function_smaller.cpp src/engine/query/search/functions/search_function_smaller_or_equal.cpp src/engine/query/search/functions/search_function_prefix.cpp src/engine/query/search/query_search.cpp src/engine/query/search/query_parameters.cpp src/engine/query/data_without_typing.cpp src/engine/query/insert/query_insert.cpp src/engine/storage/row.cpp src/engine/types/types.cpp src/engine/types/type_int.cpp src/engine/types/type.cpp src/engine/types/type_double.cpp src/engine/types/type_string.cpp src/misc/misc.cpp src/misc/slow_log.cpp src/dump/append_log_manager.cpp src/dump/dump_saver.cpp src/dump/dump_loader.cpp src/dump/save_dump_manager.cpp src/logger/logger.cpp src/config/config.cpp src/config/config_loader.cpp src/engine/table_index/table_index_info.cpp src/engine/table_index/table_index.cpp src/engine/kdtree/kd_vertex.cpp src/engine/kdtree/boundary.cpp src/engine/kdtree/query_boundary.cpp src/engine/kdtree/pivot.cpp src/engine/kdtree/search_tasks.cpp 

SRCS_INTEGRAL_TESTS=src/scripts/integral_tests.cpp

OBJS_SHUFFLA=$(subst .cpp,.o,$(SRCS_SHUFFLA))
OBJS_INTEGRAL_TESTS=$(subst .cpp,.o,$(SRCS_INTEGRAL_TESTS))

all: shuffla-server integral_tests

shuffla-server: $(OBJS_SHUFFLA)
	g++ $(LDFLAGS) -o bin/shuffla-server $(OBJS_SHUFFLA) $(LDLIBS)

integral_tests: $(OBJS_INTEGRAL_TESTS)
	g++ $(LDFLAGS) -o bin/integral_tests $(OBJS_INTEGRAL_TESTS) $(LDLIBS)

depend: .depend_shuffla .depend_integral_tests

.depend_shuffla: $(SRCS_SHUFFLA)
	rm -f .depend_shuffla
	$(CXX) $(CPPFLAGS) -MM $^>>.depend_shuffla;

.depend_integral_tests: $(SRCS_INTEGRAL_TESTS)
	rm -f .depend_integral_tests
	$(CXX) $(CPPFLAGS) -MM $^>>.depend_integral_tests;

clean:
	$(RM) $(OBJS_SHUFFLA) $(OBJS_INTEGRAL_TESTS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend_shuffla .depend_integral_tests
