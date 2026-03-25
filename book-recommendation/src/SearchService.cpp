#include "SearchService.h"

#include <cctype>

using namespace std;


string SearchService::toLower(const string& text) {
    string out;
    out.reserve(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        out.push_back(static_cast<char>(tolower(static_cast<unsigned char>(text[i]))));
    }
    return out;
}

vector<Book> SearchService::searchByKeyword(const vector<Book>& books, const string& keyword) const {
    vector<Book> out;
    const string needle = toLower(keyword);
    for (size_t i = 0; i < books.size(); ++i) {
        const string title = toLower(books[i].getTitle());
        const string author = toLower(books[i].getAuthor());
        if (title.find(needle) != string::npos || author.find(needle) != string::npos) {
            out.push_back(books[i]);
        }
    }
    return out;
}

vector<Book> SearchService::filterByGenre(const vector<Book>& books, const string& genre) const {
    GenreFilter filter(genre);
    return applyFilter(books, filter);
}

vector<Book> SearchService::filterByMinYear(const vector<Book>& books, int year) const {
    MinYearFilter filter(year);
    return applyFilter(books, filter);
}

vector<Book> SearchService::filterByMinRating(const vector<Book>& books, double minRating) const {
    MinRatingFilter filter(minRating);
    return applyFilter(books, filter);
}

vector<Book> SearchService::applyChain(const vector<Book>& books, const FilterChain& chain) const {
    vector<Book> out;
    for (size_t i = 0; i < books.size(); ++i) {
        if (chain.matches(books[i])) {
            out.push_back(books[i]);
        }
    }
    return out;
}

vector<Book> SearchService::applyFilter(const vector<Book>& books, const BookFilter& filter) const {
    vector<Book> out;
    for (size_t i = 0; i < books.size(); ++i) {
        if (filter.matches(books[i])) {
            out.push_back(books[i]);
        }
    }
    return out;
}

void SearchService::sortByRatingDesc(vector<Book>& books) const {
    sortBooks(books, [](const Book& a, const Book& b) {
        if (a.getAvgRating() == b.getAvgRating()) {
            return a.getPopularity() > b.getPopularity();
        }
        return a.getAvgRating() > b.getAvgRating();
    });
}

void SearchService::sortByYearDesc(vector<Book>& books) const {
    sortBooks(books, [](const Book& a, const Book& b) {
        if (a.getYear() == b.getYear()) {
            return a.getAvgRating() > b.getAvgRating();
        }
        return a.getYear() > b.getYear();
    });
}
