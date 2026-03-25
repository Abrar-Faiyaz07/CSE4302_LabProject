#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include <algorithm>
#include <string>
#include <vector>

#include "Book.h"
#include "BookFilter.h"

using namespace std;


class SearchService {
public:
    vector<Book> searchByKeyword(const vector<Book>& books, const string& keyword) const;
    vector<Book> filterByGenre(const vector<Book>& books, const string& genre) const;
    vector<Book> filterByMinYear(const vector<Book>& books, int year) const;
    vector<Book> filterByMinRating(const vector<Book>& books, double minRating) const;
    vector<Book> applyChain(const vector<Book>& books, const FilterChain& chain) const;
    void sortByRatingDesc(vector<Book>& books) const;
    void sortByYearDesc(vector<Book>& books) const;

    template <typename Comparator>
    void sortBooks(vector<Book>& books, Comparator comparator) const {
        sort(books.begin(), books.end(), comparator);
    }

private:
    vector<Book> applyFilter(const vector<Book>& books, const BookFilter& filter) const;
    static string toLower(const string& text);
};

#endif
