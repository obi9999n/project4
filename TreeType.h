#ifndef TREETYPE_H
#define TREETYPE_H

#include <string>
#include <fstream>
typedef int ItemType;
struct TreeNode;

class TreeType
{
public:
  TreeType();                             // constructor
  TreeType(const TreeType &originalTree); // copy constructor
  ~TreeType();                            // destructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const;
  ItemType GetItem(ItemType item, bool &found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void operator=(const TreeType &originalTree);
  void Print() const;
  void LevelOrderPrint() const;
  void PrintAncestors(int value);
  void PreOrderPrint(TreeNode *node) const;
  void PostOrderPrint(TreeNode *node) const;
  int GetSuccessor(int value);
  void mirrorImage(TreeType &t);

private:
  TreeNode *root;
  TreeType *ptrToSuccessor(TreeNode *&tree);
};
#endif
