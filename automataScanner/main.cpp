#include <iostream>
#include <string>
using namespace std;

int getNextState(int state, char character)
{
    if (state == 0 && character == '(')
        return 1;
    if (state == 1 && character == '0')
        return 2;
    if (state == 1 && character == '1')
        return 2;
    if (state == 1 && character == '2')
        return 2;
    if (state == 1 && character == '3')
        return 2;
    if (state == 1 && character == '4')
        return 2;
    if (state == 1 && character == '5')
        return 2;
    if (state == 1 && character == '6')
        return 2;
    if (state == 1 && character == '7')
        return 2;
    if (state == 1 && character == '8')
        return 2;
    if (state == 1 && character == '9')
        return 2;
    if (state == 2 && character == ',')
        return 3;
    if (state == 3 && character == '0')
        return 4;
    if (state == 3 && character == '1')
        return 4;
    if (state == 3 && character == '2')
        return 4;
    if (state == 3 && character == '3')
        return 4;
    if (state == 3 && character == '4')
        return 4;
    if (state == 3 && character == '5')
        return 4;
    if (state == 3 && character == '6')
        return 4;
    if (state == 3 && character == '7')
        return 4;
    if (state == 3 && character == '8')
        return 4;
    if (state == 3 && character == '9')
        return 4;
    if (state == 3 && character == 'r')
        return 5;
    if (state == 5 && character == 'e')
        return 6;
    if (state == 6 && character == 'd')
        return 4;
    if (state == 4 && character == ')')
        return 7;
    if (state == 7 && character == '(')
        return 8;
    if (state == 8 && character == '0')
        return 9;
    if (state == 8 && character == '1')
        return 9;
    if (state == 8 && character == '2')
        return 9;
    if (state == 8 && character == '3')
        return 9;
    if (state == 8 && character == '4')
        return 9;
    if (state == 8 && character == '5')
        return 9;
    if (state == 8 && character == '6')
        return 9;
    if (state == 8 && character == '7')
        return 9;
    if (state == 8 && character == '8')
        return 9;
    if (state == 8 && character == '9')
        return 9;
    if (state == 9 && character == ',')
        return 10;
    if (state == 10 && character == '0')
        return 13;
    if (state == 10 && character == '1')
        return 13;
    if (state == 10 && character == '2')
        return 13;
    if (state == 10 && character == '3')
        return 13;
    if (state == 10 && character == '4')
        return 13;
    if (state == 10 && character == '5')
        return 13;
    if (state == 10 && character == '6')
        return 13;
    if (state == 10 && character == '7')
        return 13;
    if (state == 10 && character == '8')
        return 13;
    if (state == 10 && character == '9')
        return 13;
    if (state == 10 && character == 'r')
        return 11;
    if (state == 11 && character == 'e')
        return 12;
    if (state == 12 && character == 'd')
        return 13;
    if (state == 13 && character == ')')
        return 14;

    return -1; // dead state
}

bool validateString(const string &input)
{
    int state = 0; // initial state
    for (char c : input)
    {
        state = getNextState(state, c);
        if (state == -1)
            return false;
    }
    return state == 14; // final state
}

int main()
{
    string inputLanguage;
    cout << "enter input language: ";
    cin >> inputLanguage;
    if (validateString(inputLanguage))
    {
        cout << "Valid string" << endl;
    }
    else
    {
        cout << "Invalid string" << endl;
    }
    return 0;
}