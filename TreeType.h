#include <string>
#include <fstream>
typedef int ItemType;
struct TreeNode;
#include "QueType.cpp"
class TreeType
{
public:
  TreeType();                     // constructor
  TreeType(const TreeType& originalTree);// copy constructor
 ~TreeType();                    // destructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
    void operator=(const TreeType& originalTree);
  void Print() const;
  void LevelOrderPrint()const;
  void PrintAncestors(int value);
  void PreOrderPrint() const;
  void PostOrderPrint() const;
  int  GetSuccessor(int value);
  void mirrorImage(TreeType& t);

private:
  TreeNode* root;
  
};

