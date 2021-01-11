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

}