#include <iostream>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    string line, first_word, word;
    while (getline(cin, line)) {
        stringstream line_stream(line);
        line_stream >> first_word;
        int idx = 1, is_acronym = 1;
        while (idx < first_word.length()) {
            if (!(line_stream >> word)) {
                is_acronym = 0;
                break;
            }
            if (tolower(first_word[idx]) != tolower(word[0])) {
                is_acronym = 0;
                break;
            }
            idx++;
        }
        if (is_acronym && !(line_stream >> word)) {
            cout << "o'_'o" << endl;
        }
        else {
            cout << "QQ" << endl;
        }
    }

    return 0;
}
