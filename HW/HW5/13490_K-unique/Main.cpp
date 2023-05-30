#include <iostream>

using namespace std;


template <typename Iterator>
Iterator k_unique(Iterator first, Iterator last, int k) {
    if (first == last) return last;

    Iterator result = first;
    int count = 1;

    while (++first != last) {
        if (*result != *first) {
            count = 1;
            ++result;
            *result = *first;
        } else if (count < k) {
            ++result;
            *result = *first;
            ++count;
        }
    }

    return ++result;
}

// remove all excpet the first k elements from every consecutive group.
//template<typename Iterator>
//Iterator k_unique(Iterator first, Iterator last, int k) {
//    // if no element
//    if (first == last) return last;
//
//    // result keeps track of the last element in the resulting container
//    Iterator result = first;
//    int i = 1;
//    while (++first != last) {
//        if (*result != *first) {
//            ++result;
//            *result = *first;
//            i = 1;
//        }
//        else if (i < k) {
//            ++i;
//            ++result;
//        }
//    }
//    return ++result;
//}


/**

1 1 2 2 2 2

7 2
aabbccd
0 1 1 2 2 2 2
1 1 1 2 2 2 2

*/
