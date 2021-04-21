#include <iostream>
using namespace std;
#include "TreeType.h"
struct TreeNode {
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};
inline TreeType::TreeType()
{
  root = NULL;
}

inline TreeType::TreeType(const TreeType &originalTree)
{
}

inline void Destroy(TreeNode *&tree);

inline TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

inline bool TreeType::IsFull() const
// Returns true if there is no room for another item
//  on the free store; false otherwise.
{
  TreeNode *location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch (std::bad_alloc exception)
  {
    return true;
  }
}

inline bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

inline int CountNodes(TreeNode *tree);

inline int TreeType::GetLength() const
// Calls recursive function CountNodes to count the
// nodes in the tree.
{
  return CountNodes(root);
}

inline int CountNodes(TreeNode *tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

inline void Retrieve(TreeNode *tree,
                     ItemType &item, bool &found);

inline ItemType TreeType::GetItem(ItemType item, bool &found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

// helper function for GetItem
inline void Retrieve(TreeNode *tree,
                     ItemType &item, bool &found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise found is false and item is unchanged.
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

inline void Insert(TreeNode *&tree, ItemType item);

inline void TreeType::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

// helper Function for PutItem
inline void Insert(TreeNode *&tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  { // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item); // Insert in left subtree.
  else
    Insert(tree->right, item); // Insert in right subtree.
}
inline void DeleteNode(TreeNode *&tree);

inline void Delete(TreeNode *&tree, ItemType item);

inline void TreeType::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
  bool found = false;
  GetItem(item, found);
  if (found)
    Delete(root, item);
  else
    cout << item << "is not in tree\n";
}

inline void Delete(TreeNode *&tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item); // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item); // Look in right subtree.
  else
    DeleteNode(tree); // Node found; call DeleteNode.
}

inline void GetPredecessor(TreeNode *tree, ItemType &data) {
  while(tree->right != nullptr){
        tree = tree->right;
        data = tree->info;
  } // while 
}

inline void DeleteNode(TreeNode *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-NULL child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{
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
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data); // Delete predecessor node.
  }
}
//Helper function for DeleteNode
inline void GetPredecessor(TreeNode *tree, ItemType &data)
// Sets data to the info member of the right-most node in tree.
  {
    while (tree->right != NULL) {
      tree = tree->right;
      data = tree->info;
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

TreeType* ptrToSuccessor(TreeNode*&tree) {
  TreeType* ptr = tree->left;
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

inline void Destroy(TreeNode *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
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



