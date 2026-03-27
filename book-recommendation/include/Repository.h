#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <string>
#include "BookRepository.h"
#include "RatingRepository.h"
#include "UserRepository.h"

using namespace std;

class Repository{
public:
    Repository();

    bool loadAll(const string& booksPath,
                 const string& usersPath,
                 const string& ratingsPath);

    bool saveAll(const string& booksPath,
                 const string& usersPath,
                 const string& ratingsPath) const;

    BookRepository& books();
    UserRepository& users();
    RatingRepository& ratings();
    const BookRepository& books() const;
    const UserRepository& users() const;
    const RatingRepository& ratings() const;

private:
    BookRepository bookRepo;
    UserRepository userRepo;
    RatingRepository ratingRepo;
};

#endif
