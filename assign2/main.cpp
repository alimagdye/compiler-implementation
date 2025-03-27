#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int getNextState(int state, char character)
{
    if (state == 0 && character == '(')
    {
        cout << "OPEN_PARENTHESIS: " << character << endl;
        return 1;
    }
    if (state == 1 && character == '0')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '1')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '2')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '3')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '4')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '5')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '6')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '7')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '8')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 1 && character == '9')
    {
        cout << "NUMBER: " << character << endl;
        return 2;
    }
    if (state == 2 && character == ',')
    {
        cout << "COMMA: " << character << endl;
        return 3;
    }
    if (state == 3 && character == '0')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '1')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '2')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '3')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '4')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '5')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '6')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '7')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '8')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == '9')
    {
        cout << "NUMBER: " << character << endl;
        return 4;
    }
    if (state == 3 && character == 'r')
        return 5;
    if (state == 5 && character == 'e')
        return 6;
    if (state == 6 && character == 'd')
    {
        cout << "COLOR: red" << endl;
        return 4;
    }
    if (state == 4 && character == ')')
    {
        cout << "CLOSE_PARENTHESIS: " << character << endl;
        return 7;
    }
    if (state == 7 && character == '(')
    {
        cout << "OPEN_PARENTHESIS: " << character << endl;
        return 8;
    }
    if (state == 8 && character == '0')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '1')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '2')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '3')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '4')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '5')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '6')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '7')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '8')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 8 && character == '9')
    {
        cout << "NUMBER: " << character << endl;
        return 9;
    }
    if (state == 9 && character == ',')
    {
        cout << "COMMA: " << character << endl;
        return 10;
    }
    if (state == 10 && character == '0')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '1')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '2')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '3')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '4')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '5')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '6')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '7')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '8')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == '9')
    {
        cout << "NUMBER: " << character << endl;
        return 13;
    }
    if (state == 10 && character == 'r')
        return 11;
    if (state == 11 && character == 'e')
        return 12;
    if (state == 12 && character == 'd')
    {
        cout << "COLOR: red" << endl;
        return 13;
    }
    if (state == 13 && character == ')')
    {
        cout << "CLOSE_PARENTHESIS: " << character << endl;
        return 14;
    }

    return -1; // dead state
}

void validateString(const string &input)
{
    int state = 0; // initial state
    for (char c : input)
    {
        state = getNextState(state, c);
        if (state == -1)
            return;
    }
}

int main()
{
    ifstream file("input.txt"); // Open the file
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return 1; // Return an error code
    }

    string line;
    while (getline(file, line))
    { // Read line by line
        validateString(line);
    }

    file.close(); // Close the file
    return 0;
}