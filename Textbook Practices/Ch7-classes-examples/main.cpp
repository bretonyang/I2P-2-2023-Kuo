#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

string &func(string &str) {
    str = "test";
    return str; // still in heap
}

string test() {
    return "abc"; /// returns a rvalue
}

int main()
{
//    string str = "abcde";
//    const string &var = test(); /// since test() returns a rvalue, var needs to be a reference to const
//
//    cout << str << endl << var << endl;
//    cout << str + ' ' + var << endl;

//    Person me, you;
//    read(cin, me);
//    read(cin, you);
//    print(cout, me) << endl;
//    print(cout, you) << endl;
//
//    Person p = add(me, you); // the return value of add() is copied into p
//    print(cout, p) << endl;
//    print(cout, add(me, you).combine(p)) << endl;

/*
    string str = "abcdefg";
    cout << str.substr(2, 3) << endl;// substring with 3 chars, starting at index 2.
    str.erase(2, 3);// erase 3 chars from str, starting at index 2.
    cout << str << endl; // abfg
    str.replace(1, 2, "xyz"); // replace 2 characters from str, starting at index 1, with "xyz"
    cout << str << endl; // axyzg
    cout << str.find("yz") << endl; // 2
    cout << (str.find("wtf") == string::npos) << endl; // true or 1
*/

    return 0;
}

/** NOTE

1. Put class definition in "MyClass.h" and class's member and nonmember function's definitions in "MyClass.cpp".

   - class's member function's definition normally should NOT be put in the class's definition,
     any function put in the class's definition in the header file is implicitly "inline".

   - Define class definition and related nonmember function declarations in the header file.

   - The header file serves as the "interface", and cpp file serves as the "implementation".

2. "struct" and "class" have almost the same mechanism, the only difference is:
    - members of "struct" are "public" by default.
    - members of "class" are "private" by default.

3. The "this" pointer:
   - By default, "this" is implicitly passed to the member function as a "const pointer".

   - If const is declared after the parameter list of a member function, then "this" is passed to that function
     as a "const pointer to const object".

   - Inside a member function, whether it's defined in class's body, or outside the class's body, any direct use of
     a member of the class is assumed to be an reference through "this", i.e. "this->member_name".

4. A "class" is itself a scope.

   - Member function bodies can use other members of their class that are declared after the function.
     This is because member declarations are comlpiles first, then member function's definitions, if any.

   - When defining a function outside the class body, we use the "scope resolution operator ::" to specify that
     the function is inside the scope of the class.
     The compiler thus treats its definition as inside the class's scope.

5. Objects are copied when:
   - initialize a variable
   - pass an object by value
   - return an object by value

*/

















