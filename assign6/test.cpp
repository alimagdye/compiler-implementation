#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// This class handles loading and querying the predictive table
class PredictiveParser
{
private:
    vector<string> terminals;               // top header (terminal symbols)
    map<string, map<string, string>> table; // map[non-terminal][terminal] = production

public:
    // Load table from CSV file
    bool loadTable(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file!" << endl;
            return false;
        }

        string line;
        vector<vector<string>> rawTable;

        // Parse CSV into rawTable
        while (getline(file, line))
        {
            stringstream ss(line);
            string cell;
            vector<string> row;

            while (getline(ss, cell, ','))
            {
                // Trim whitespace
                cell.erase(0, cell.find_first_not_of(" \t\r\n"));
                cell.erase(cell.find_last_not_of(" \t\r\n") + 1);
                row.push_back(cell);
            }

            rawTable.push_back(row);
        }

        file.close();

        if (rawTable.empty())
        {
            cerr << "Empty table." << endl;
            return false;
        }

        // First row contains terminals (skip first empty cell)
        terminals.assign(rawTable[0].begin() + 1, rawTable[0].end());

        // Remaining rows: non-terminal in first column, rest are productions
        for (size_t i = 1; i < rawTable.size(); ++i)
        {
            const string &nonTerminal = rawTable[i][0];
            for (size_t j = 1; j < rawTable[i].size(); ++j)
            {
                table[nonTerminal][terminals[j - 1]] = rawTable[i][j];
            }
        }

        return true;
    }

    // Get production rule given non-terminal and terminal
    string getProduction(const string &nonTerminal, const string &terminal) const
    {
        map<string, map<string, string>>::const_iterator ntIt = table.find(nonTerminal);
        if (ntIt != table.end())
        {
            map<string, string>::const_iterator tIt = ntIt->second.find(terminal);
            if (tIt != ntIt->second.end())
            {
                return tIt->second;
            }
        }
        return "Not Found";
    }
};

// Sample usage
int main()
{
    PredictiveParser parser;

    if (!parser.loadTable("predictive_table.txt"))
    {
        return 1;
    }

    string nonTerminal, terminal;
    cout << "Enter non-terminal: ";
    cin >> nonTerminal;
    cout << "Enter terminal: ";
    cin >> terminal;

    string production = parser.getProduction(nonTerminal, terminal);
    cout << "Production: " << production << endl;

    return 0;
}
