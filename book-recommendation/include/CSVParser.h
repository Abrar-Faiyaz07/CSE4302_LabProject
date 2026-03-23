#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>

using namespace std;


class CSVParser {
public:
    static vector<vector<string> > readRows(const string& path, bool skipHeader);
    static bool writeRows(const string& path, const vector<string>& header,
                          const vector<vector<string> >& rows);

    static vector<string> splitLine(const string& line);
    static string trim(const string& input);
    static bool toInt(const string& input, int& output);
    static bool toDouble(const string& input, double& output);
    static string joinSet(const vector<string>& values, char delimiter);
    static vector<string> splitTokenList(const string& input, char delimiter);
};

#endif
