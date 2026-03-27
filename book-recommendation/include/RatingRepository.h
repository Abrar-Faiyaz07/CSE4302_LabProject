#ifndef RATINGREPOSITORY_H
#define RATINGREPOSITORY_H
#include <string>
#include <vector>
#include "Rating.h"

using namespace std;

class RatingRepository{
public:
    bool load(const string& path);
    bool save(const string& path) const;
    const vector<Rating>& getAll() const;
    vector<Rating>& getAllMutable();
    void addOrUpdate(int userId, int bookId, int score);

private:
    vector<Rating> ratings;
};

#endif
