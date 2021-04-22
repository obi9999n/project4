#include <iostream>
#include "TreeType.h"
#include "QueType.cpp"
#include <string>

using namespace std;

struct TreeNode
{
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};

TreeType::TreeType()
{
  root = NULL;
}

TreeType::TreeType(const TreeType &originalTree)
{
  CopyTree(root, originalTree.root);
} // copy constructor

void Destroy(TreeNode *&tree)
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  } // if
} // Destroy

TreeType::~TreeType()
{
  Destroy(root);
} // destructor, calls recursive function Destroy to destroy the tree

// Returns true if there is no room for another item on the free store; false otherwise.
bool TreeType::IsFull() const
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
bool TreeType::IsEmpty() const
{
  return root == NULL;
}

// Calls recursive function CountNodes to count the nodes in the tree.
int TreeType::GetLength() const
{
  return CountNodes(root);
}

// Post: returns the number of nodes in the tree.
int CountNodes(TreeNode *tree)
{
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

// helper function for GetItem
void Retrieve(TreeNode *tree, ItemType &item, bool &found)
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
ItemType TreeType::GetItem(ItemType item, bool &found)
{
  Retrieve(root, item, found);
  return item;
}

// helper Function for PutItem
void Insert(TreeNode *&tree, ItemType item)
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
void TreeType::PutItem(ItemType item)
{
  Insert(root, item);
}

void TreeType::DeleteItem(ItemType item)
{
  bool found = false;
  GetItem(item, found);
  if (found)
    Delete(root, item);
  else
    cout << item << "is not in tree\n";
} // calls recursive function Delete to delete item from tree

void TreeType::Delete(TreeNode *&tree, ItemType item)
{
  if (item < tree->info)
    Delete(tree->left, item); // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item); // Look in right subtree.
  else
    DeleteNode(tree); // Node found; call DeleteNode.
}

void GetPredecessor(TreeNode *tree, ItemType &data)
{
  while (tree->right != nullptr)
  {
    tree = tree->right;
    data = tree->info;
  } // while
}
TreeNode *TreeType::ptrToSuccessor(TreeNode *&tree)
{
  TreeNode *ptr = tree->left;
  while (ptr->left != NULL)
  {
    ptr = tree->left;
  }
  return ptr;
}

void TreeType::DeleteNode(TreeNode *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-NULL child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{

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
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    TreeNode *succ = ptrToSuccessor(tree->right);
    tree->info = succ->info;
    Delete(tree->right, succ->info);
  }
}

// Helper function for Print
void inOrderTraverse(TreeNode *tree)
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left); // Print left subtree.
    cout << tree->info << "  ";
    inOrderTraverse(tree->right); // Print right subtree.
  }
}

void TreeType::Print() const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root);
}
void PreOrderTraverse(TreeNode *node)
{
  TreeNode *temp = node;
  if (temp != NULL)
  {
    cout << temp->info << " ";
    PreOrderTraverse(temp->left);
    PreOrderTraverse(temp->right);
  }
}
void TreeType::PreOrderPrint() const
{
  PreOrderTraverse(root);
}

void PostOrderTraverse(TreeNode *node)
{
  TreeNode *temp = node;
  if (temp != NULL)
  {
    PostOrderTraverse(temp->left);
    PostOrderTraverse(temp->right);
    cout << temp->info << " ";
  }
}

void TreeType::PostOrderPrint() const
{
  PostOrderTraverse(root);
}

void TreeType::PrintAncestors(int value)
{
  int newVal = value;
  if (value == root->info)
  {
    cout << value << " has no ancestors\n";
    return;
  }
  while (newVal != root->info)
  {
    TreeNode *temp = root;
    while (temp->right->info != newVal || temp->left->info != newVal)
    {
      if (temp->info < newVal)
      {
        temp = temp->right;
      }
      else if (temp->info > newVal)
      {
        temp = temp->left;
      }
      if (temp->right == NULL && temp->left == NULL)
      {
        cout << "Item is not in the tree";
        return;
      }
    }
    cout << temp->info << " ";
    newVal = temp->info;
  }
} // print ancestors

int TreeType::GetSuccessor(int value)
{
  TreeNode *temp = root;
  while (temp->right->info != value || temp->left->info != value)
  {
    if (temp->left->info == value)
    {
      temp = temp->right;
      break;
    }
    else if (temp->left->info == value)
    {
      temp = temp->left;
      break;
    }
    else if (temp->info < value)
    {
      temp = temp->right;
    }
    else if (temp->info > value)
    {
      temp = temp->left;
    }
  }
  TreeNode *done = ptrToSuccessor(temp);
  return done->info;
}

// helper function for Mirror Image
void mirror(TreeNode *&copy, const TreeNode *originalTree)
{
  copy = new TreeNode;
  if (originalTree != NULL)
  {
    mirror(copy->left, originalTree->right);
    mirror(copy->right, originalTree->left);
  } // if
} // copy is the root of a tree that is a mirror Image of

void TreeType::mirrorImage(TreeType &t)
{
  mirror(t.root, root);
}

void TreeType::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}
void CopyTree(TreeNode *&copy,
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

void TreeType::operator=(const TreeType &originalTree)
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

void TreeType::LevelOrderPrint() const
{
  int count = 0;
  int level = 0;
  TreeNode *temp = root;
  if (temp == NULL)
    return;

  // Create an empty queue for level order traversal
  QueType<TreeNode *> q;
  // Enqueue Root and initialize height
  q.Enqueue(temp);

  while (q.IsEmpty() == false)
  {
    // Print front of queue and remove it from queue
    TreeNode *node = q.Dequeue();
    if (node != nullptr)
    {
      cout << node->info << " ";
    }
    else
    {
      cout << "-";
    }
    count++;
    if (count == (2 ^ level))
    {
      cout << endl;
      level++;
    }
    /* Enqueue left child */
    if (node != nullptr)
    {
      q.Enqueue(node->left);

      /*Enqueue right child */
      q.Enqueue(node->right);
    }
  }
}