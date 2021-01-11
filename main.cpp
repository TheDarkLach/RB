/*red black tree insertion by faizan karim*/
//no option to reset tree :/

#include <iostream>
#include <cstring>
#include <fstream>
//colors ucuz you cant have a red and black tree without colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
//yea so black on black is not cool
#define BLUE    "\033[36m"

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

//Read from file
void READ(Node* &head) 
{
  char in[10000];
  char fileName[100];
  int modif[100];
  int siz = 0;
  int count = 0;
  memset(in, 0, 10000);
  memset(fileName, 0, 100);
  memset(modif, 0, 100);
  //read in file name
  cout << endl << "What is the name of the file?" << endl;
  cin.get(fileName, 30);
  cin.clear();
  cin.ignore(100000, '\n');
  streampos size;
  ifstream file(fileName, ios::in | ios::binary | ios::ate);
  if (file.is_open()) 
  {
    size = file.tellg();
    file.seekg(0, ios::beg);
    file.read(in, size);
    file.close();
    parse(in, modif, count);  //parse input to modif array
    cout << "IN: ";
    for (int i = 0; i < 100; i++) 
    {
      if (modif[i] != 0) 
      {
        cout << modif[i] << " ";
        siz++;
      }
    }
    cout << endl << "Size: " << siz << endl;;
    //add to tree
    Node* curr = NULL;
    Node* prev = NULL;
    for (int i = 0; i < siz; i++) 
    {
      if(modif[i] == 0)
      {
        break;
      } 
      curr = head;
      ADD(head, curr, prev, modif[i]);
    }
  } 
}

//print functions, similar to binary
void PRINT(Node* root, Trunk *prev, bool isLeft) 
{
  if (root == NULL) 
  {
    return;
  }
  char* prev_str = (char*)("    ");
  Trunk *trunk = new Trunk(prev, prev_str);
  PRINT(root->getLeft(), trunk, true);
  if (!prev) 
  {
    trunk -> str = (char*)("---");
  }
  else if (isLeft)
   {
    trunk -> str = (char*)(".---");
    prev_str = (char*)("   |");
  }
  else 
  {
    trunk -> str = (char*)("`---");
    prev -> str = prev_str;
  }
  showTrunks(trunk);
  if (root->getColor() == 0)
  {  
    //black
    cout << BLUE << root->getData() << RESET << endl;
  } 
  else 
  {  
    //red
    cout << RED << root->getData() << RESET << endl;
  }
  if (prev) 
  {
    prev -> str = prev_str;
  }
  trunk -> str = (char*)("   |");
  PRINT(root->getRight(), trunk, false);
}

//parsing
void parse(char* in, int* modif, int &count) 
{
  int l = 0;  //keeps track of # of chars before space
  for (int i = 0; i < strlen(in); i++) 
  {
    if (in[i] == ' ') 
    {
      if (l == 1) 
      {
        int temp = 0;
        temp = in[i-1] - '0';
        modif[count] = temp;
        count++;
        l = 0;
      } 
      else 
      {
        int temp = 0;
        for (int a = 0; a < l; a++) 
        {
          temp = 10 * temp + (in[i-l+a] - '0');
        }
        modif[count] = temp;
        count++;
        l = 0;
      }
    } 
    else 
    {
      int temp = 0;
      l++;
      if (i == strlen(in) - 1) 
      {  
        //last possible pair of chars
        for (int a = 0; a < l; a++) 
        {
            temp = 10 * temp + (in[i+a+1-l] - '0');
        }
        modif[count] = temp;
        count++;
      }
    }
  } 
}