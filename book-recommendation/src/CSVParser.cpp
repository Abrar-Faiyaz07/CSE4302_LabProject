#include "CSVParser.h"
#include "AppExceptions.h"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;


vector<vector<string> > CSVParser::readRows(const string& path, bool skipHeader) {
    vector<vector<string> > rows;
    ifstream input(path.c_str());
    if (!input.is_open()) {
        throw DataAccessException("Unable to open CSV file for read: " + path);
    }

    string line;
    bool first = true;
    while (getline(input, line)) {
        if (first && skipHeader) {
            first = false;
            continue;
        }
        first = false;

        if (line.empty()) {
            continue;
        }
        rows.push_back(splitLine(line));
    }

    return rows;
}

bool CSVParser::writeRows(const string& path, const vector<string>& header,
                          const vector<vector<string> >& rows) {
    ofstream output(path.c_str(), ios::trunc);
    if (!output.is_open()) {
        throw DataAccessException("Unable to open CSV file for write: " + path);
    }

    for (size_t i = 0; i < header.size(); ++i) {
        output << header[i];
        if (i + 1 < header.size()) {
            output << ',';
        }
    }
    output << '\n';

    for (size_t i = 0; i < rows.size(); ++i) {
        const vector<string>& row = rows[i];
        for (size_t j = 0; j < row.size(); ++j) {
            string cell = row[j];
            bool hasComma = cell.find(',') != string::npos;
            bool hasQuote = cell.find('"') != string::npos;
            if (hasQuote) {
                string escaped;
                for (size_t k = 0; k < cell.size(); ++k) {
                    escaped.push_back(cell[k]);
                    if (cell[k] == '"') {
                        escaped.push_back('"');
                    }
                }
                cell = escaped;
            }
            if (hasComma || hasQuote) {
                output << '"' << cell << '"';
            } else {
                output << cell;
            }
            if (j + 1 < row.size()) {
                output << ',';
            }
        }
        output << '\n';
    }

    return true;
}

vector<string> CSVParser::splitLine(const string& line) {
    vector<string> cells;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current.push_back('"');
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            cells.push_back(trim(current));
            current.clear();
        } else {
            current.push_back(c);
        }
    }
    cells.push_back(trim(current));

    return cells;
}

string CSVParser::trim(const string& input) {
    size_t start = 0;
    while (start < input.size() && isspace(static_cast<unsigned char>(input[start]))) {
        ++start;
    }

    size_t end = input.size();
    while (end > start && isspace(static_cast<unsigned char>(input[end - 1]))) {
        --end;
    }

    return input.substr(start, end - start);
}

bool CSVParser::toInt(const string& input, int& output) {
    char* endPtr = NULL;
    long value = strtol(input.c_str(), &endPtr, 10);
    if (endPtr == input.c_str() || *endPtr != '\0') {
        return false;
    }
    output = static_cast<int>(value);
    return true;
}

bool CSVParser::toDouble(const string& input, double& output) {
    char* endPtr = NULL;
    double value = strtod(input.c_str(), &endPtr);
    if (endPtr == input.c_str() || *endPtr != '\0') {
        return false;
    }
    output = value;
    return true;
}

string CSVParser::joinSet(const vector<string>& values, char delimiter) {
    ostringstream out;
    for (size_t i = 0; i < values.size(); ++i) {
        out << values[i];
        if (i + 1 < values.size()) {
            out << delimiter;
        }
    }
    return out.str();
}

vector<string> CSVParser::splitTokenList(const string& input, char delimiter) {
    vector<string> tokens;
    string current;
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (c == delimiter) {
            string t = trim(current);
            if (!t.empty()) {
                tokens.push_back(t);
            }
            current.clear();
        } else {
            current.push_back(c);
        }
    }
    string t = trim(current);
    if (!t.empty()) {
        tokens.push_back(t);
    }
    return tokens;
}
