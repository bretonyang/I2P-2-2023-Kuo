#include <stdio.h>
#include <stdlib.h>
#include "function.h"

/* You need to implement the following functions, good luck! */
Node *buildDoublyCircularLinkedList(int n){
    Node* head = createNode(1);
    Node* lastNode =  head;
    for (int i = 2; i <= n; i++) {
        Node* newNode = createNode(i);
        newNode->prevPtr = lastNode;
        lastNode->nextPtr = newNode;
        lastNode = lastNode->nextPtr;
    }
    lastNode->nextPtr = head;
    head->prevPtr = lastNode;
    return head;
}

Node *getNextPersonOut(int peopleLeft, int m, Node *startNode){
    Node* curNode = startNode;
    int steps = m % peopleLeft;
    if (!steps) {
        curNode = curNode->prevPtr;
    }
    else {
        for (int i = 1; i < steps; i++) {
            curNode = curNode->nextPtr;
        }
    }
    return curNode;
}

void connectNodes(Node *personInFront, Node *personInBack){
    personInFront->nextPtr = personInBack;
    personInBack->prevPtr = personInFront;
}

void swapNodes(Node *personInFront, Node *personInBack){
    Node* nextOfBack = personInBack->nextPtr;
    Node* prevOfFront = personInFront->prevPtr;
    prevOfFront->nextPtr = personInBack;
    nextOfBack->prevPtr = personInFront;
    personInFront->nextPtr = nextOfBack;
    personInBack->prevPtr = prevOfFront;
    personInFront->prevPtr = personInBack;
    personInBack->nextPtr = personInFront;
}
