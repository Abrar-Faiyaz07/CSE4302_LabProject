#include "Book.h"

Book::Book()
    : id(0), year(0), avgRating(0.0), ratingCount(0), popularity(0) {}

Book::Book(int id, const std::string& title, const std::string& author,
           const std::string& genre, int year, double avgRating,
           int ratingCount, int popularity)
    : id(id), title(title), author(author), genre(genre), year(year),
      avgRating(avgRating), ratingCount(ratingCount), popularity(popularity) {}

int Book::getId() const { return id; }
const std::string& Book::getTitle() const { return title; }
const std::string& Book::getAuthor() const { return author; }
const std::string& Book::getGenre() const { return genre; }
int Book::getYear() const { return year; }
double Book::getAvgRating() const { return avgRating; }
int Book::getRatingCount() const { return ratingCount; }
int Book::getPopularity() const { return popularity; }

void Book::setTitle(const std::string& value) { title = value; }
void Book::setAuthor(const std::string& value) { author = value; }
void Book::setGenre(const std::string& value) { genre = value; }
void Book::setYear(int value) { year = value; }
void Book::setPopularity(int value) { popularity = value; }

bool Book::isValid() const {
    return id > 0 && !title.empty() && !author.empty() && !genre.empty() &&
           year > 0 && avgRating >= 0.0 && avgRating <= 5.0 && ratingCount >= 0 && popularity >= 0;
}

void Book::applyNewRating(int score) {
    if (score < 1 || score > 5) {
        return;
    }

    double total = avgRating * ratingCount;
    total += score;
    ++ratingCount;
    avgRating = total / ratingCount;
    ++popularity;
}
