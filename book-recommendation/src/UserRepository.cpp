#include "UserRepository.h"
#include <exception>
#include <vector>
#include "CSVParser.h"
using namespace std;
namespace{
vector<string> toVector(const set<string>& values){
    vector<string> out;
    for (set<string>::const_iterator it = values.begin(); it != values.end(); ++it){
        out.push_back(*it);
    }
    return out;
}

string serializeReadBooks(const set<int>& books){
    string out;
    bool first = true;
    for (set<int>::const_iterator it = books.begin(); it != books.end(); ++it){
        if (!first){
            out += ';';
        }
        first = false;
        out += to_string(*it);
    }
    return out;
}

string serializeRatedBooks(const map<int, int>& ratings){
    string out;
    bool first = true;
    for (map<int, int>::const_iterator it = ratings.begin(); it != ratings.end(); ++it){
        if (!first){
            out += ';';
        }
        first = false;
        out += to_string(it->first) + ":" + to_string(it->second);
    }
    return out;
}
}

bool UserRepository::load(const string& path){
    users.clear();

    vector<vector<string> > rows;
    try{
        rows = CSVParser::readRows(path, true);
    }
    catch (const exception&){
        return false;
    }

    for (size_t i = 0; i < rows.size(); ++i){
        const vector<string>& row = rows[i];
        if (row.size() < 6){
            continue;
        }

        int id = 0;
        if (!CSVParser::toInt(row[0], id)){
            continue;
        }

        string password;
        if (row.size() >= 7){
            password = row[6];
        }
        User user(id, row[1], password);

        vector<string> genres = CSVParser::splitTokenList(row[2], ';');
        for (size_t g = 0; g < genres.size(); ++g){
            user.addPreferredGenre(genres[g]);
        }

        vector<string> authors = CSVParser::splitTokenList(row[3], ';');
        for (size_t a = 0; a < authors.size(); ++a){
            user.addPreferredAuthor(authors[a]);
        }

        vector<string> readBooks = CSVParser::splitTokenList(row[4], ';');
        for (size_t r = 0; r < readBooks.size(); ++r){
            int bookId = 0;
            if (CSVParser::toInt(readBooks[r], bookId)){
                user.markBookRead(bookId);
            }
        }

        vector<string> ratedBooks = CSVParser::splitTokenList(row[5], ';');
        for (size_t rb = 0; rb < ratedBooks.size(); ++rb){
            vector<string> pair = CSVParser::splitTokenList(ratedBooks[rb], ':');
            if (pair.size() != 2){
                continue;
            }
            int bookId = 0;
            int score = 0;
            if (CSVParser::toInt(pair[0], bookId) && CSVParser::toInt(pair[1], score)){
                user.addOrUpdateRating(bookId, score);
            }
        }

        if (user.isValid()){
            users.push_back(user);
        }
    }

    rebuildIndex();
    recomputeNextId();
    return true;
}

bool UserRepository::save(const string& path) const{
    vector<string> header;
    header.push_back("id");
    header.push_back("name");
    header.push_back("preferred_genres");
    header.push_back("preferred_authors");
    header.push_back("read_books");
    header.push_back("rated_books");
    header.push_back("password");

    vector<vector<string> > rows;
    for (size_t i = 0; i < users.size(); ++i){
        const User& u = users[i];
        vector<string> row;

        row.push_back(to_string(u.getId()));
        row.push_back(u.getName());
        row.push_back(CSVParser::joinSet(toVector(u.getPreferredGenres()), ';'));
        row.push_back(CSVParser::joinSet(toVector(u.getPreferredAuthors()), ';'));
        row.push_back(serializeReadBooks(u.getReadBooks()));
        row.push_back(serializeRatedBooks(u.getRatedBooks()));
        row.push_back(u.getPassword());

        rows.push_back(row);
    }

    try{
        return CSVParser::writeRows(path, header, rows);
    }
    catch (const exception&){
        return false;
    }
}

const vector<User>& UserRepository::getAll() const{ return users; }
vector<User>& UserRepository::getAllMutable(){ return users; }

const User* UserRepository::findById(int id) const{
    map<int, size_t>::const_iterator it = indexById.find(id);
    if (it == indexById.end()){
        return NULL;
    }
    return &users[it->second];
}

User* UserRepository::findByIdMutable(int id){
    map<int, size_t>::iterator it = indexById.find(id);
    if (it == indexById.end()){
        return NULL;
    }
    return &users[it->second];
}

User& UserRepository::createUser(const string& name, const string& password){
    users.push_back(User(nextId, name, password));
    ++nextId;
    rebuildIndex();
    return users.back();
}

void UserRepository::rebuildIndex(){
    indexById.clear();
    for (size_t i = 0; i < users.size(); ++i){
        indexById[users[i].getId()] = i;
    }
}

void UserRepository::recomputeNextId(){
    nextId = 1;
    for (size_t i = 0; i < users.size(); ++i){
        if (users[i].getId() >= nextId){
            nextId = users[i].getId() + 1;
        }
    }
}
