#include <iostream>
#include <QueType.cpp>
#include "TreeType.h"

using namespace std;

struct TreeNode {
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};

inline TreeType::TreeType() {
  root = NULL;
}

inline TreeType::TreeType(const TreeType &originalTree) {
  CopyTree(root, originalTree.root);
} // copy constructor

inline void Destroy(TreeNode *&tree) {
  if (tree != NULL) {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  } // if
}

inline TreeType::~TreeType() {
  Destroy(root);
} // calls recursive function Destroy to destroy the tree

// Returns true if there is no room for another item on the free store; false otherwise.
inline bool TreeType::IsFull() const {
  TreeNode *location;
  try {
    location = new TreeNode;
    delete location;
    return false;
  } catch (std::bad_alloc exception) {
    return true;
  }
} 

// Returns true if the tree is empty; false otherwise.
inline bool TreeType::IsEmpty() const {
  return root == NULL;
}

// Calls recursive function CountNodes to count the nodes in the tree.
inline int TreeType::GetLength() const {
  return CountNodes(root);
}

// Post: returns the number of nodes in the tree.
inline int CountNodes(TreeNode *tree) {
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

// helper function for GetItem
inline void Retrieve(TreeNode *tree, ItemType &item, bool &found)
{
  if (tree == NULL)
    found = false; // item is not found.
  else if (item < tree->info)
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found); // Search right subtree.
  else
  {
    item = tree->info; // item is found.
    found = true;
  }
}

// Calls recursive function Retrieve to search the tree for item.
inline ItemType TreeType::GetItem(ItemType item, bool &found) {
  Retrieve(root, item, found);
  return item;
}

// helper Function for PutItem
inline void Insert(TreeNode *&tree, ItemType item) {
  if (tree == NULL) { // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  } // if
  else if (item < tree->info) {
    Insert(tree->left, item); // Insert in left subtree.
  } // else if
  else {
    Insert(tree->right, item); // Insert in right subtree.
  } // else
} // insert 

// Calls recursive function Insert to insert item into tree.
inline void TreeType::PutItem(ItemType item) {
  Insert(root, item);
}

inline void TreeType::DeleteItem(ItemType item) {
  bool found = false;
  GetItem(item, found);
  if (found)
    Delete(root, item);
  else
    cout << item << "is not in tree\n";
}

inline void Delete(TreeNode *&tree, ItemType item){
if (item < tree->info) {
  Delete(tree->left, item); // Look in left subtree.
} // if
else if (item > tree->info) {
  Delete(tree->right, item); // Look in right subtree.
} // else if
else {
  DeleteNode(tree); // Node found; call DeleteNode.
} // else
}

inline void GetPredecessor(TreeNode *tree, ItemType &data) {
  while(tree->right != NULL){
        tree = tree->right;
        data = tree->info;
  } // while 
}

inline void DeleteNode(TreeNode *&tree) {
  ItemType data;
  TreeNode *tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    TreeNode* succ = ptrToSuccessor(tree->right);
    tree->info = succ->info;
    Delete(tree->left, succ->info); // Delete predecessor node.
  }
}

// Helper function for Print
inline void inOrderTraverse(TreeNode *tree)
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left); // Print left subtree.
    cout << tree->info << "  ";
    inOrderTraverse(tree->right); // Print right subtree.
  }
}

inline void TreeType::Print() const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root);
}
inline void TreeType::PreOrderPrint() const
{ // Implement this function, You may call a helper function
  // Then Remove the following stub statement
  cout << "PreOrderPrint stub has been called\n";
}
inline void TreeType::PostOrderPrint() const
{
  // Implement this function, You may call a helper function
  // Then Remove the following stub statement
  cout << "Post OrderPrint stub has been called\n";
}
inline void TreeType::PrintAncestors(int value)
{
  // Implement this function, You may call a helper function
  // Then Remove the following stub statement
  cout << "PrintAncestors() has been called\n";
}

 TreeNode* ptrToSuccessor(TreeNode*&tree) {
  TreeNode* ptr = tree->left;
  while (ptr->left != NULL) {
    ptr = tree->left;
  }
  return ptr;
}

inline int TreeType::GetSuccessor(int value)
{
  
}
// helper function for Mirror Image
inline void mirror(TreeNode *&copy, const TreeNode *originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{ // implement this function
}

inline void TreeType::mirrorImage(TreeType &t)
{
  // calls the helper function mirror
}

inline void TreeType::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}
inline void CopyTree(TreeNode *&copy,
                     const TreeNode *originalTree)
// Post: copy is the root of a tree that is a duplicate
// of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

inline void TreeType::operator=(const TreeType &originalTree)
// Calls recursive function CopyTree to copy originalTree
// into root.
{
  {
    if (&originalTree == this)
      return;      // Ignore assigning self to self
    Destroy(root); // Deallocate existing tree nodes
    CopyTree(root, originalTree.root);
  }
}

inline void TreeType::LevelOrderPrint(TreeType *tree) const
{ //Implement this function, you May use a data structure
}



