#include "RatingRepository.h"
#include <exception>
#include "CSVParser.h"

using namespace std;

bool RatingRepository::load(const string& path){
    ratings.clear();
    vector<vector<string> > rows;
    try{
        rows = CSVParser::readRows(path, true);
    }
    catch (const exception&){
        return false;
    }

    for (size_t i = 0; i < rows.size(); ++i){
        const vector<string>& row = rows[i];
        if (row.size() < 3){
            continue;
        }
        int userId = 0;
        int bookId = 0;
        int score = 0;
        if (!CSVParser::toInt(row[0], userId) || !CSVParser::toInt(row[1], bookId) || !CSVParser::toInt(row[2], score)){
            continue;
        }
        Rating rating(userId, bookId, score);
        if (rating.isValid()){
            ratings.push_back(rating);
        }
    }

    return true;
}

bool RatingRepository::save(const string& path) const{
    vector<string> header;
    header.push_back("user_id");
    header.push_back("book_id");
    header.push_back("score");

    vector<vector<string> > rows;
    for (size_t i = 0; i < ratings.size(); ++i){
        const Rating& r = ratings[i];
        vector<string> row;
        row.push_back(to_string(r.getUserId()));
        row.push_back(to_string(r.getBookId()));
        row.push_back(to_string(r.getScore()));
        rows.push_back(row);
    }

    try{
        return CSVParser::writeRows(path, header, rows);
    }
    catch (const exception&){
        return false;
    }
}

const vector<Rating>& RatingRepository::getAll() const{ return ratings; }
vector<Rating>& RatingRepository::getAllMutable(){ return ratings; }

void RatingRepository::addOrUpdate(int userId, int bookId, int score){
    for (size_t i = 0; i < ratings.size(); ++i){
        if (ratings[i].getUserId() == userId && ratings[i].getBookId() == bookId){
            ratings[i].setScore(score);
            return;
        }
    }
    ratings.push_back(Rating(userId, bookId, score));
}
