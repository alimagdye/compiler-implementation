#include <iostream>
#include <fstream>
#include <sstream> // Required for stringstream
using namespace std;

string getNextState(string state, char character)
{
    ifstream transitionFile("transitions.txt");
    if (!transitionFile)
    {
        cerr << "Error opening file: transitions.txt" << endl;
        return "-1";
    }

    // read line by line from line 3
    int lineCount = 0;
    string line = "";
    string fileState = "", fileResultState = "";
    char fileCharacter = ' ';
    while (getline(transitionFile, line))
    {
        lineCount++;
        if (lineCount >= 3)
        {
            stringstream lineStatesAndChar(line);
            for (int i = 0; i < 3; i++)
            {
                if (i == 0)
                    lineStatesAndChar >> fileState; // extract the file state
                else if (i == 1)
                    lineStatesAndChar >> fileCharacter; // extract the file character
                else
                    lineStatesAndChar >> fileResultState; // extract the file result state
            }

            // if fileState == state and fileCharacter == character:
            if (fileState == state && fileCharacter == character)
            {
                transitionFile.close();
                return fileResultState;
            }
        }
    }

    // if transition doesn't exist
    transitionFile.close();
    return "-1"; // dead state
}

bool isFinal(string state)
{
    ifstream transitionsFile("transitions.txt");
    if (!transitionsFile)
    {
        cerr << "Error opening file: transitions.txt" << endl;
        return false;
    }

    string firstLine;
    if (!getline(transitionsFile, firstLine)) // Read the first line
    {
        transitionsFile.close();
        return false; // If the file is empty, return false
    }

    string fileState;
    stringstream firstLineStates(firstLine); // Use stringstream to extract states easily

    // while looping over each state in firstLineStates
    while (firstLineStates >> fileState) // put each state from the first line states in fileState variable
    {
        if (state == fileState) // Compare with the given state
        {
            transitionsFile.close();
            return true;
        }
    }

    transitionsFile.close();
    return false;
}

string isToken(string token)
{
    ifstream tokensFile("tokens.txt");
    if (!tokensFile)
    {
        cerr << "Error opening file: tokens.txt" << endl;
        return "";
    }

    string line = "", fileToken = "", description = "";

    while (getline(tokensFile, line))
    {
        stringstream tokenAndDescription(line);
        tokenAndDescription >> fileToken;
        if (token == fileToken)
        {
            // get the description from the same line
            tokenAndDescription >> description;
            tokensFile.close();
            return description;
        }
    }

    // if token doesn't exits in the file
    tokensFile.close();
    return "";
}

void writeError(string wrongToken)
{
    ofstream outputFile("output.txt", ios::app);

    if (!outputFile)
    {
        cerr << "Error opening file: output.txt" << endl;
        return;
    }

    outputFile << "Error wrong token:" << wrongToken << endl;

    outputFile.close();
}

void writeToken(string description, string token)
{
    ofstream outputFile("output.txt", ios::app);

    if (!outputFile)
    {
        cerr << "Error opening file: output.txt" << endl;
        return;
    }

    outputFile << description << ": " << token << endl;

    outputFile.close();
}

// Scanner function
void scan(const string &fileName) // O(n^2) where n is every character in inputFile, and transtions
{
    ifstream inputFile(fileName); // open the file
    if (!inputFile)               // if it doesn't exist
    {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    ofstream outputFile("output.txt");
    if (!outputFile) // if it doesn't exist
    {
        cerr << "Error opening file: output.txt" << endl;
        return;
    }
    outputFile.clear();
    outputFile.close();

    // create int varaible state: intialize it with 0
    string previousState = "0", nextState = "0";
    // create str variable token: intialize it with ""
    string token = "";
    // create str variable describtion to have the describtion of the token
    string description = "";
    string line = "";
    while (getline(inputFile, line)) // read line by line
    {
        // do:  + " " to make dead state at the end of the loop
        line = line + " ";
        // loop over line string
        for (int i = 0; i < line.size(); i++)
        {
            // when reaching the end of the line
            if (previousState == "0" && i == line.size() - 1)
                break; // break and go to next line
            // call getNextState(state, on every char) and update state with its result
            nextState = getNextState(previousState, line[i]);
            // if state is dead state:
            if (nextState == "-1")
            {
                // yes: get its previousState and check is it final state from finals in transition-table:
                if (isFinal(previousState))
                {
                    // yes: check if token exists in tokens.txt
                    description = isToken(token);
                    if (description.size())
                    {
                        // yes: get the describe of token from tokens.txt
                        // and write to output.txt: describe: token
                        writeToken(description, token);
                        i--;
                        // then reset token to has new tokens
                        token = "";
                        previousState = nextState = "0";
                    }
                    // else: token dosen't exist means wrong token, so make error
                    else
                        writeError(token);
                }
                // else: not final means wrong token, so make error
                else
                    writeError(token);
            }
            // else
            else
            {
                previousState = nextState;
                // accumalate token with every new charcter from line
                token += line[i];
            }
        }
    }

    inputFile.close(); // close the file
    cout << "Tokenization complete. Output written to output.txt" << endl;
}

int main()
{

    scan("input.txt");

    return 0;
}
