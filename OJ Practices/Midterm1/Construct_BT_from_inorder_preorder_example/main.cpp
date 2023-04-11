// C++ program for the above approach

#include <bits/stdc++.h>
using namespace std;

// C++ program to check if given inorder
// and preorder traversals of size N are
// valid for a binary tree or not
bool checkInorderPreorderUtil(
    int inStart, int inEnd,
    int& preIndex, int preorder[],
    unordered_map<int, int>& inorderIndexMap)
{
    if (inStart > inEnd)
        return true;

    // Build the current Node
    int rootData = preorder[preIndex];
    preIndex++;

    // If the element at current Index
    // is not present in the inorder
    // then tree can't be built
    if (inorderIndexMap.find(rootData)
        == inorderIndexMap.end())
        return false;

    int inorderIndex = inorderIndexMap[rootData];

    // If the inorderIndex does not fall
    // within the range of the inorder
    // traversal of the current tree
    // then return false
    if (!(inStart <= inorderIndex
          && inorderIndex <= inEnd))
        return false;

    int leftInorderStart = inStart;
    int leftInorderEnd = inorderIndex - 1;
    int rightInorderStart = inorderIndex + 1;
    int rightInorderEnd = inEnd;

    // Check if the left subtree can be
    // built from the inorder traversal
    // of the left subtree and preorder
    if (!checkInorderPreorderUtil(
            leftInorderStart, leftInorderEnd,
            preIndex, preorder, inorderIndexMap))
        return false;

    // Check if the left subtree can be
    // built from the inorder traversal
    // of the left subtree and preorder
    else
        return checkInorderPreorderUtil(
            rightInorderStart, rightInorderEnd,
            preIndex, preorder, inorderIndexMap);
}

// Function to check for the validation of
// inorder and preorder
string checkInorderPreorder(
    int pre[], int in[], int n)
{
    unordered_map<int, int> inorderIndexMap;

    for (int i = 0; i < n; i++)
        inorderIndexMap[in[i]] = i;

    int preIndex = 0;
    if (checkInorderPreorderUtil(
            0, n - 1, preIndex,
            pre, inorderIndexMap)) {
        return "Yes";
    }
    else {
        return "No";
    }
}

// Driver Code
int main()
{
    int pre[] = { 1, 2, 4, 5, 7, 3, 6, 8 };
    int in[] = { 4, 2, 5, 7, 1, 6, 8, 3 };
    int N = sizeof(pre) / sizeof(pre[0]);
    cout << checkInorderPreorder(pre, in, N);

    return 0;
}
