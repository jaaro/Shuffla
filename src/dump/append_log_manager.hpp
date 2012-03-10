#ifndef APPENDLOGMANAGER_H
#define APPENDLOGMANAGER_H

#include "../engine/query/query.hpp"

class AppendLogManager
{
public:
    AppendLogManager();
    virtual ~AppendLogManager();

    void append(const Query* query);
protected:
private:
    bool is_enabled;
};

#endif // APPENDLOGMANAGER_H
