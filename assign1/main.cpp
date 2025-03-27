#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to check if the string is a valid color
bool isColor(const string &word)
{
    return (word == "red" || word == "blue" || word == "green");
}

void scanner(const string &input)
{
    int length = input.size();
    int i = 0;

    while (i < length)
    {
        char character = input[i];

        // Skip spaces
        if (isspace(character))
        {
            i++;
            continue;
        }

        // Open Parenthesis (
        if (character == '(')
        {
            cout << "OPEN_PARENTHESIS: " << character << "\n";
            i++;
        }

        // Number 0-9
        else if (isdigit(character))
        {
            cout << "NUMBER: " << character << "\n";
            i++;
        }

        // Comma ,
        else if (character == ',')
        {
            cout << "COMMA: " << character << "\n";
            i++;
        }

        // Close Parenthesis )
        else if (character == ')')
        {
            cout << "CLOSE_PARENTHESIS: " << character << "\n";
            i++;
        }

        // Possible color (red, blue, green)
        else if (isalpha(character))
        {
            string word;
            while (i < length && isalpha(input[i]))
            { // Collect letters
                word += input[i];
                i++;
            }

            if (isColor(word))
            {
                cout << "COLOR: " << word << "\n";
            }
            else
            {
                cout << "Error: Unknown token " << word << "\n";
                return;
            }
        }

        // Unknown character
        else
        {
            cout << "Error: Unknown token " << character << "\n";
            return;
        }
    }
}

int main()
{
    string input;
    cout << "Enter input: ";
    getline(cin, input); // Use getline to allow spaces in input
    scanner(input);

    return 0;
}
