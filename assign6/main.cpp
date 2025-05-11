#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <fstream>
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
    cerr << "Tokenization incomplete" << endl;
    outputFile.close();
    exit(1); // exit the program with error code 1
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
void scan(string fileName) // O(n^2) where n is every character in inputFile, and transtions
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
    outputFile.clear(); // clear the file content before writing
    outputFile.close(); // close the file

    // create int varaible state: intialize it with 0
    string previousState = "0", nextState = "0";
    // create string variable token: intialize it with ""
    string token = "";
    // create string variable describtion to have the describtion of the token
    string description = "";
    string line = "";                // to read line by line
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

/// below is the code for the parser
/////////////////////////////////////////////////////////////////////////////////

// Requirements for LL(1):
// Scanner, and getNextToken(File: outputFile): returns each token for each call.
string getNextToken(ifstream &outputFile)
{
    // get the next line if there is a line in the file
    string line = "", token = "";
    if (getline(outputFile, line))
    {
        // get the second string from the line which is the token
        stringstream lineStream(line);
        lineStream >> token; // get the first string from the line
        lineStream >> token; // get the second string from the line
        return token;        // return the token
    }

    return "$"; // return $ if there is no remaining line in the file
}

// isTerminal(string): returns true if the string is a terminal of the grammar.
bool isTerminal(string str)
{
    // open predictive-table.txt file
    ifstream predictiveTableFile("predictive-table.txt");
    if (!predictiveTableFile)
    {
        cerr << "Error opening file: predictive-table.txt" << endl;
        return false;
    }
    string line = "", fileNonTerminal = "";
    // get the first line
    getline(predictiveTableFile, line);
    // get every string in this line and check if it equal the string given
    stringstream lineStream(line);
    while (lineStream >> fileNonTerminal)
    {
        if (fileNonTerminal == str) // if it equals the string given, then it's non-terminal
        {
            predictiveTableFile.close();
            return false; // not terminal
        }
    }
    // if it doesn't equal to any non-terminal
    predictiveTableFile.close();
    return true; // terminal
}
// Use stack to save the non-terminal of the grammar.
// getRule(token, non-terminal): returns the rule that parse to the given token and non-terminal from the predictive table in array in reverse order. E.g., [`Expr`, `Term`]
vector<string> getRule(string token, string nonTerminal)
{
    ifstream predictiveTableFile("predictive-table.txt");
    if (!predictiveTableFile)
    {
        cerr << "Error opening file: predictive-table.txt" << endl;
        return {"~"};
    }
    string line = "", fileToken = "", fileNonTerminal = "", ruleString = "";
    vector<string> rule = {}; // vector to store the rule
    // read line by line from line 3
    int lineCount = 0;
    int stringCount = 0;
    while (getline(predictiveTableFile, line))
    {
        lineCount++;
        if (lineCount >= 3) // start from line 3
        {
            stringstream lineStream(line);
            stringCount = 0; // reset stringCount for each line
            while (lineStream >> ruleString)
            {
                if (stringCount == 0)
                    fileNonTerminal = ruleString;
                else if (stringCount == 1)
                    fileToken = ruleString;
                else
                {
                    if (fileToken == token && fileNonTerminal == nonTerminal)
                    {
                        rule.push_back(ruleString); // add the rule to the vector
                        ruleString = "";            // reset ruleString for the next token
                    }
                }
                stringCount++;
            }
        }
    }

    int j = rule.size() - 1; // get the last index of the vector
    string temp = "";        // temporary variable to store the rule
    // push the rule to the vector in reverse order
    for (int i = 0; i < rule.size() / 2.0; i++)
    {
        temp = rule[i];
        rule[i] = rule[j];
        rule[j] = temp; // swap the elements in the vector
        j--;
    }
    predictiveTableFile.close();
    return rule;
}

bool parse(string fileName)
{
    ifstream outputFile(fileName); // open the file
    if (!outputFile)               // if it doesn't exist
    {
        cerr << "Error opening file: " << fileName << endl;
        return false;
    }
    string firstNonTerminal = "Exp"; // the first non-terminal of the grammar
    // initialize the stack with "$"
    stack<vector<string>> stack; // stack of arrays of strings
    stack.push({"$"});           // push the first element to the stack

    // read first token
    string token = getNextToken(outputFile); // get the first token

    // stack.push(getRule(first token, first non-terminal)) add the rule
    stack.push(getRule(token, firstNonTerminal)); // push the first rule to the stack

    string element = "";

    // while stack top isn’t "$"":
    while (stack.top().back() != "$")
    {
        // get the top array, and last element from it
        element = stack.top().back(); // get the last element of the top array
        cout << element << " -> " << token << endl;
        // if it equals ~: return false
        if (element == "~")
        {
            outputFile.close(); // close the file
            cout << "parse failed" << endl;
            return false; // not valid string
        }
        // if it’s terminal:
        else if (isTerminal(element))
        {
            // if it doesn’t equal the token: return false
            if (element != token && element != "0")
            {
                outputFile.close(); // close the file
                cout << "parse failed" << endl;
                return false; // not valid string
            }
            // if it equals token:
            else
            {

                // while stack top has only one element and it’s not $: remove it
                while (stack.top().size() == 1 && stack.top().back() != "$")
                {
                    stack.pop(); // pop the top array if it has only one element
                }
                // if (element == "0")
                // {
                //     continue;
                // }
                if (stack.top().back() != "$")
                    stack.top().pop_back(); // remove the last element from the top array

                if (token != "$" && element != "0")
                    // Make the pointer points to the next token.
                    token = getNextToken(outputFile);
            }
        }
        // if it's non-terminal: stack.push(getRule(first token, this element))
        else
            stack.push(getRule(token, element)); // push the rule to the stack
    }
    // reaching here means the stack only has "$". If getNextToken() gives "$": return true.
    if (stack.top().back() == "$" && token == "$")
    {
        cout << "parse success" << endl;
        outputFile.close(); // close the file
        return true;        // valid string
    }
    cout << "parse failed" << endl;
    outputFile.close(); // close the file
    return false;       // not valid string
}

int main()
{
    scan("input.txt");
    parse("output.txt");
    // notice:
    // (a/b-c) is valid in parser and scanner
    // (a/b-c)b is not valid in parser but valid in scanner
    // (a/b+a)*c is valid in parser and scanner
    // (a/b-c)* isn't valid in parser but valid in scanner
    // (a/b-c)*(a/b-c) is valid in parser and scanner
    return 0;
}