#ifndef NODE_H
#define NODE_H

using namespace std;

class Node 
{
 public:
  //constructor & deleter
  Node();
  ~Node();
  //setters
  void setData(int);
  void setRight(Node*);
  void setLeft(Node*);
  void setColor(int);
  void setParent(Node*);
  //getters
  int getData();
  Node* getRight();
  Node* getLeft();
  int getColor();
  Node* getParent();
private:
  int data;
  Node* right;
  Node* left;
  int color;  //0 = black, 1 = red, i think. might be the other way around
  Node* parent;
};
#endif

//
