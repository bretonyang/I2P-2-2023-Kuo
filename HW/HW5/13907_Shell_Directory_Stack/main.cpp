#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<vector<string>> commands;
map<string, vector<string>> parentOfDir;

vector<string> parse(string path) {
    vector<string> result;
    string word;
    stringstream ss(path);
    while (getline(ss, word, '/')) {
        result.push_back(word);
    }
    if (result.size() == 0 && result[0] == "") {
        result[0] = "/";
    }
    else if (result.size() > 0) {
        if (result[0] == "") {

        }
    }
    return result;
}

/**
cd ../..
cd token/abc
cd /dfs/bfs
cd ../etc
cd /
cd ./etc
cd ./
cd lib
*/

void process()
{
    parentOfDir["/"].push_back("/");
    stack<string> st;
    string current = "/root";
    string old = "/root";

    for (vector<string> command : commands) {
        if (command[0] == "cd") {
            if (command.size() == 1) {
                // no argument, change to "/root"
                old = current;
                current = "/root";
            }
            else if (command[1] == "-") {
                // change to old
                swap(current, old);
            }
            else {
                vector<string> path = parse(command[1]);
                for (auto c : path) {
                    cout << c << ' ';
                }
                cout << endl;
            }
        }
        else if (command[0] == "pwd") {

        }
        else if (command[0] == "pushd") {

        }
        else if (command[0] == "popd") {

        }
        else if (command[0] == "dirs") {

        }
    }
}

int main()
{
    string line;
    while (getline(cin, line)) {
        vector<string> command;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            command.push_back(word);
        }
        commands.push_back(command);
    }
//    for (auto c : commands) {
//        for (auto cc : c) {
//            cout << cc << " ";
//        }
//        cout << endl;
//    }

    process();

    return 0;
}

/**

/
    root
    etc
    usr
        local
            bin
    opt <--
    var
    dev

stack:

cd ../etc
pwd
cd -
pwd
cd /
pwd
cd ./usr
pwd
cd local/bin
pwd
cd ..
pwd
cd -
pwd
cd /opt
pwd
pushd
pushd /var
dirs
pushd /dev <-- show curWorkingDir and stackFromTop
dirs
pushd <-- swap current: /dev with top: /var
dirs
cd -  <-- go back to previoud dir: /dev before pushd
dirs
popd  <-- Pop top of stack, and change workingDir to popped value
dirs
popd  <-- Pop top of stack, and change workingDir to popped value
dirs
popd

*/
