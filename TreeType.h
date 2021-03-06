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
  void PreOrderPrint() const;
  void PostOrderPrint() const;
  int GetSuccessor(int value);
  void mirrorImage(TreeType &t);
  void DeleteNode(TreeNode *&tree);
  void Delete(TreeNode *&tree, ItemType item);
  int CountNodes(TreeNode *tree) const;
  void CopyTree(TreeNode *&copy, const TreeNode *originalTree);

private:
  TreeNode *root;
  TreeNode *ptrToSuccessor(TreeNode *&tree);
  void Destroy(TreeNode *&tree);
  void Retrieve(TreeNode *tree, ItemType &item, bool &found);
  void Insert(TreeNode *&tree, ItemType item);
  void GetPredecessor(TreeNode *tree, ItemType &data);

  void mirror(TreeNode *&copy, const TreeNode *originalTree);
};
#endif
