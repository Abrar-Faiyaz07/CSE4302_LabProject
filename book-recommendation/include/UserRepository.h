#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include <map>
#include <string>
#include <vector>
#include "User.h"

using namespace std;

class{
public:
    bool load(const string& path);
    bool save(const string& path) const;
    const vector<User>& getAll() const;
    vector<User>& getAllMutable();
    const User* findById(int id) const;
    User* findByIdMutable(int id);
    User& createUser(const string& name, const string& password);

private:
    vector<User> users;
    map<int, size_t> indexById;
    int nextId = 1;
    void rebuildIndex();
    void recomputeNextId();
};

#endif
