#ifndef APPENDLOGMANAGER_H
#define APPENDLOGMANAGER_H

#include "../engine/query/query.hpp"

/**
 * Append log. If enabled, saves all commands that are modifying database.
 */
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
