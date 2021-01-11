/*red black tree insertion by faizan karim*/

#include <iostream>
#include <cstring>
#include <fstream>
//colors ucuz you cant have a red and black tree without colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"

#include "node.h"

using namespace std;

//struct Trunk for print method
struct Trunk 
{
  Trunk *prev;
  char* str;

  Trunk(Trunk *prev, char* str) 
  {
    this->prev = prev;
    this->str = str;
  }
};

//helper method for printing
void showTrunks(Trunk *p) 
{
  if (p == NULL)
  {
      return;
  }

  showTrunks(p -> prev);

  cout << p -> str;
}

//woo prototypes
void ADD(Node* &head, Node* &curr, Node*& prev, int val);
void READ(Node* &head);
void PRINT(Node* root, Trunk *prev, bool isLeft);
void parse(char* in, int* modif, int &count);
//functions for balancing/fixing tree
void balance(Node* &head, Node* &curr);
void rotateLeft(Node* &head, Node* &curr);
void rotateRight(Node* &head, Node* &curr);

int main()
{
    //variables
  char input[10]; //user input
  char read[10000];  //file input
  int modif[100]; //parsed input for insertion
  Node* head = NULL;
  //program
  cout << "Red Black Tree Insertiom" << endl;
  bool run = true;
  while (run) 
  {
    //cout << RED << "hello world" << RESET << endl;
    //cout << BLUE << "YO" << RESET << endl;
    cout << endl << "You can: add, read, print, and quit." << endl;
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(input, "add") == 0) 
    {
      int val;
      cout << ">Add value: ";
      cin >> val;
      cin.clear();
      cin.ignore(10000, '\n');
      Node* curr = head;
      Node* prev = NULL;
      ADD(head, curr, prev, val);
      if(curr != head) balance(head, curr);
      cout << endl << val << " has been added:" << endl;
    }
    else if (strcmp(input, "read") == 0) 
    {
      //make sure arrays are clear
      READ(head);
    }
    else if (strcmp(input, "print") == 0) 
    {
      PRINT(head, NULL, false);
    }
    else if (strcmp(input, "quit") == 0) 
    {
      cout << endl << "Quitting..." << endl;
      run = false;
    }
    else 
    {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  return 0;
}

//balancing
//https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
//that site usually sucks tho
void balance(Node* &head, Node* &curr) 
{
  Node* parent = NULL;
  Node* grandparent = NULL;
  while ((curr != head) && (curr->getColor() != 0) && ((curr->getParent())->getColor() == 1)) 
  {
    parent = curr->getParent();
    grandparent = parent->getParent();
    //Case A: parent = left child of grandparent
    if (parent == grandparent->getLeft()) 
    {
      Node* uncle = grandparent->getRight();
      //Case 1: uncle = red, then only recolor
      if (uncle != NULL && uncle->getColor() != 0) 
      {
        grandparent->setColor(1);//red
        parent->setColor(0);//black
        uncle->setColor(0);//black
        curr = grandparent;
      }
      else 
      {
        //Case 2: curr = right child of parent, then rotate left
        if (curr == parent->getRight()) 
        {
        rotateLeft(head, parent);
        curr = parent;
        parent =  curr->getParent();
        }
        //Case 3: curr - left child of parent, then rotate right
        rotateRight(head, grandparent);
        //swap colors of parent and grandparent
        int tempC = parent->getColor();
        parent->setColor(grandparent->getColor());
        grandparent->setColor(tempC);
        curr = parent;
      }
    }
    //Case B: parent = right child of grandparent
    else 
    {
      Node* uncle = grandparent->getLeft();
      //Case 1: uncle = red, then onyl recolor
      if (uncle != NULL && uncle->getColor() != 0) 
      {
        grandparent->setColor(1);//red
        parent->setColor(0);//black
        uncle->setColor(0);//black
        curr = grandparent;
      }
      else 
      {
        //Case 2: curr = left child of parent, then rotate right
        if (curr == parent->getLeft()) 
        {
        rotateRight(head, parent);
        curr = parent;
        parent = curr->getParent();
    	}
        //Case 3: curr = right child of parent, then rotate left
        rotateLeft(head, grandparent);
        //swap color of parent and grandparent
        int tempC = parent->getColor();
        parent->setColor(grandparent->getColor());
        grandparent->setColor(tempC);
        curr = parent;
      }
    }
  }
  head->setColor(0);
}

void rotateLeft(Node* &head, Node* &curr) 
{
  Node* rightPtr = curr->getRight(); 
  //
  curr->setRight(rightPtr->getLeft()); 
  if (curr->getRight() != NULL) 
  {
    (curr->getRight())->setParent(curr); 
  }
  rightPtr->setParent(curr->getParent());
  //if working with head
  if (curr->getParent() == NULL) 
  {
    head = rightPtr; 
  } 
  else if (curr == (curr->getParent())->getLeft()) 
  {
    (curr->getParent())->setLeft(rightPtr); 
  } 
  else
  {
    (curr->getParent())->setRight(rightPtr); 
  }  
  rightPtr->setLeft(curr); 
  curr->setParent(rightPtr);
}

void rotateRight(Node* &head, Node* &curr) 
{
  Node *leftPtr = curr->getLeft(); 
  //
  curr->setLeft(leftPtr->getRight()); 
  if (curr->getLeft() != NULL) 
  {
    (curr->getLeft())->setParent(curr); 
  }  
  leftPtr->setParent(curr->getParent());
  //if working with head
  if (curr->getParent() == NULL) 
  {
    head = leftPtr; 
  }
  else if (curr == (curr->getParent())->getLeft()) 
  {
    (curr->getParent())->setLeft(leftPtr); 
  } 
  else 
  {
    (curr->getParent())->setRight(leftPtr);
  }
  leftPtr->setRight(curr); 
  curr->setParent(leftPtr);
}

void ADD(Node* &head, Node* &curr, Node* &prev, int val) {
  if (head == NULL) 
  {
    head = new Node();
    curr = head;
    head->setData(val);
    head->setColor(0);  //head is always black
    return;
  } 
  else 
  {
    if (val < curr->getData()) 
    {  
      //lower goes left
      prev = curr;
      curr = curr->getLeft();
      if (curr == NULL) 
      {  
        //if empty then insert
        curr = new Node();
        curr->setData(val);
        prev->setLeft(curr);
        curr->setParent(prev);
        balance(head, curr);  //balance tree
        return;
      } 
      else 
      {  //if !empty then keep going
	    ADD(head, curr, prev, val);
      }
    }
    else 
    {
      prev = curr;
      curr = curr->getRight();
        if (curr == NULL) 
        {
        //if empty then insert
        curr = new Node();
        curr->setData(val);
        prev->setRight(curr);
        curr->setParent(prev);
        balance(head, curr);  //balance tree
        return;
      } 
      else 
      {  //if !empty then keep going
	    ADD(head, curr, prev, val);
      }
    }
  }
}