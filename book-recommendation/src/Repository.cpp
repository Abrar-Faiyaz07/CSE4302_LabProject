#include "Repository.h"

using namespace std;

Repository::Repository(){}

bool Repository::loadAll(const string& booksPath, const string& usersPath, const string& ratingsPath){
    bool okBooks = bookRepo.load(booksPath);
    bool okUsers = userRepo.load(usersPath);
    bool okRatings = ratingRepo.load(ratingsPath);
    return okBooks && okUsers && okRatings;
}

bool Repository::saveAll(const string& booksPath, const string& usersPath, const string& ratingsPath) const {
    bool okBooks = bookRepo.save(booksPath);
    bool okUsers = userRepo.save(usersPath);
    bool okRatings = ratingRepo.save(ratingsPath);
    return okBooks && okUsers && okRatings;
}

BookRepository& Repository::books(){
    return bookRepo;
}
UserRepository& Repository::users(){
    return userRepo;
}
RatingRepository& Repository::ratings(){
    return ratingRepo;
}

const BookRepository& Repository::books() const{
    return bookRepo;
}
const UserRepository& Repository::users() const{
    return userRepo;
}
const RatingRepository& Repository::ratings() const{
    return ratingRepo;
}
