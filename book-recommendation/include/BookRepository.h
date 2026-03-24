#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <map>
#include <string>
#include <vector>

#include "Book.h"

using namespace std;


class BookRepository {
public:
    bool load(const string& path);
    bool save(const string& path) const;

    const vector<Book>& getAll() const;
    vector<Book>& getAllMutable();

    const Book* findById(int id) const;
    Book* findByIdMutable(int id);

private:
    vector<Book> books;
    map<int, size_t> indexById;
    void rebuildIndex();
};

#endif
