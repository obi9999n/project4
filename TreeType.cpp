#include <iostream>
#include "TreeType.h"

using namespace std;

struct TreeNode
{
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
  CopyTree(root, originalTree.root);
} // copy constructor

inline void Destroy(TreeNode *&tree)
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  } // if
}

inline TreeType::~TreeType()
{
  Destroy(root);
} // calls recursive function Destroy to destroy the tree

// Returns true if there is no room for another item on the free store; false otherwise.
inline bool TreeType::IsFull() const
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

// Returns true if the tree is empty; false otherwise.
inline bool TreeType::IsEmpty() const
{
  return root == NULL;
}

// Calls recursive function CountNodes to count the nodes in the tree.
inline int TreeType::GetLength() const
{
  return CountNodes(root);
}

// Post: returns the number of nodes in the tree.
inline int CountNodes(TreeNode *tree)
{
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
inline ItemType TreeType::GetItem(ItemType item, bool &found)
{
  Retrieve(root, item, found);
  return item;
}

// helper Function for PutItem
inline void Insert(TreeNode *&tree, ItemType item)
{
  if (tree == NULL)
  { // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  } // if
  else if (item < tree->info)
  {
    Insert(tree->left, item); // Insert in left subtree.
  }                           // else if
  else
  {
    Insert(tree->right, item); // Insert in right subtree.
  }                            // else
} // insert

// Calls recursive function Insert to insert item into tree.
inline void TreeType::PutItem(ItemType item)
{
  Insert(root, item);
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

inline void GetPredecessor(TreeNode *tree, ItemType &data)
{
  while (tree->right != nullptr)
  {
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
  while (tree->right != NULL)
  {
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
{
  PreOrderTransversal(root);
}
inline void PreOrderTransversal(TreeNode *node)
{
  TreeNode *temp = node;
  if (temp == NULL)
  {
    return;
  }
  cout << temp->info << " ";
  PreOrderTransversal(temp->left);
  PreOrderTransversal(temp->right);
}
inline void TreeType::PostOrderPrint() const
{
  PostOrderTransversal(root);
}
inline void PostOrderTransversal(TreeNode *node)
{
  TreeNode *temp = node;
  if (temp == NULL)
  {
    return;
  }
  PostOrderTransversal(temp->left);
  PostOrderTransversal(temp->right);
  cout << temp->info << " ";
}
//prints all ancestors of a value
inline void TreeType::PrintAncestors(int value)
{
  //Creates a moveable variable
  int newVal = value;
  //Ends if he value is in the root node
  if (value == root->info)
  {
    cout << value << " has no ancestors\n";
    return;
  }
  //Goes until all ancestors have been printed
  while (newVal != root->info)
  {
    //temporary node for transversal
    TreeNode *temp = root;
    //Goes until it finds the ancestor of newVal
    while (temp->right->info != newVal && temp->left->info != newVal)
    {
      //Goes right or left depending on if newVal is more or less than the node
      if (temp->info < newVal)
      {
        temp = temp->right;
      }
      else if (temp->info > newVal)
      {
        temp = temp->left;
      }
      //If the value is not in the tree
      if (temp->right == NULL && temp->left == NULL)
      {
        cout << "Item is not in the tree";
        return;
      }
    }
    //Prints ancestor
    cout << temp->info << " ";
    //Makes ancestor the new value to find (ex: printancestors(10) newval = 10 then 6 then 15)
    newVal = temp->info;
  }
}

<<<<<<< HEAD
TreeNode* ptrToSuccessor(TreeNode *&tree)
=======
TreeNode *ptrToSuccessor(TreeNode *&tree)
>>>>>>> 3741bfbff29fbcb1114296b12defb3375e7d2817
{
  TreeNode *ptr = tree->left;
  while (ptr->left != NULL)
  {
    ptr = tree->left;
  }

  return ptr;
}

inline int TreeType::GetSuccessor(int value)
{
}
// helper function for Mirror Image
inline void mirror(TreeNode *&copy, const TreeNode *originalTree)
{
  copy = new TreeNode;
  if (originalTree != NULL)
  {
    mirror(copy->left, originalTree->right);
    mirror(copy->right, originalTree->left);
  } // if
} // copy is the root of a tree that is a mirror Image of

inline void TreeType::mirrorImage(TreeType &t)
{
  mirror(t.root, root);
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
