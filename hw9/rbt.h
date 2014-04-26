/*
 * rbbst.h
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes 
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
	RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
	: Node<KeyType, ValueType> (k, v, p)
	  { color = red; }

	virtual ~RedBlackNode () {}

	Color getColor () const
	{ return color; }

	void setColor (Color c)
	{ color = c; }
  
  void toggleColor()
  {
    if (color == red)
      color = black;
    else
      color = red;
  }
        /* The type casting allows us to treat getParent, getLeft, getRight
           as returning RedBlackNode instead of Node */
	virtual RedBlackNode<KeyType, ValueType> *getParent () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_parent; }

	virtual RedBlackNode<KeyType, ValueType> *getLeft () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_left; }

	virtual RedBlackNode<KeyType, ValueType> *getRight () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_right; }

protected:
	Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/
//need to compare colors
 
template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  using BinarySearchTree<KeyType, ValueType>::root;
	void add (KeyType key, ValueType value){
		/* This one is yours to implement.
		It should add the (key, value) pair to the tree, 
		making sure that it remains a valid Red-Black Tree.
		If the key is already in the tree (with a possibly different associated value),
		then it should overwrite the value with the new one.
		We strongly recommend defining suitable (private) helper functions. */
		
		RedBlackNode<KeyType, ValueType> *addition= new RedBlackNode<KeyType, ValueType>(key, value, NULL);
		
		//with no parent, you're black
		if (root==NULL){
			addition->setColor (black);
			
			//need an assignment operator
			root=addition;
			return;
		}

    RedBlackNode<KeyType, ValueType> *currNode = (RedBlackNode<KeyType, ValueType> *)root;
    
		addition->setColor (red);
    while (currNode != NULL)
    {
      // If key is matching, just update the value and we are done
      //  because the tree is not changed otherwise.
      if (currNode->getKey() == addition->getKey())
      {
        currNode->setValue(addition->getValue());
        duplicates++;
        return;
      }
      else if (currNode->getKey() > addition->getKey())
      {
        if (currNode->getLeft() == NULL)
        {
          addition->setParent(currNode);
          currNode->setLeft(addition);
          break;
        }
        currNode = currNode->getLeft();        
      }
      else
      {
        if (currNode->getRight() == NULL)
        {
          addition->setParent(currNode);
          currNode->setRight(addition);
          break;
        }
        currNode = currNode->getRight();        
      }
    }

		//if red red
		if (addition->getParent()->getColor()==red){
			fixtree(addition);
		}
	} // add
  void printall() 
  {
    std::cout << "Duplicate count = " << duplicates << "\n";
    printrbtree((RedBlackNode<KeyType, ValueType> *)root);
    std::cout<<"\n";
  }
private:
	//root node
	//RedBlackNode<KeyType, ValueType>   *root;
  int                                duplicates;
	RedBlackNode<KeyType, ValueType>   *findMyUncle(RedBlackNode<KeyType, ValueType>   *rbNode);
  bool                               AmIaRightChild(RedBlackNode<KeyType, ValueType> *rbNode);
  bool                               AmIaLeftChild(RedBlackNode<KeyType, ValueType> *rbNode);
  void                               RightRotateAndRecolor(RedBlackNode<KeyType, ValueType> *rbNode);
  void                               LeftRotate(RedBlackNode<KeyType, ValueType> *rbNode);
  
  void printrbtree(RedBlackNode<KeyType, ValueType> *r);
  void fixtree (RedBlackNode<KeyType, ValueType> *rbNode);
};
template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::fixtree(RedBlackNode<KeyType, ValueType> *rbNode)
{
  if (rbNode != root && rbNode->getParent()->getColor() == red)
  {
    RedBlackNode<KeyType, ValueType> *rbNodeUncle = findMyUncle(rbNode);
    // Case 1 : parent and uncle both red.
    if (rbNodeUncle != NULL && rbNodeUncle->getColor() == red)
    {
      // both parent and uncle are red, hence recolor parent, uncle and grandparent.
      //  IMPORTANT: the fact the uncle is NOT NULL implies the presence of grandparent.
      RedBlackNode<KeyType, ValueType>   *rbNodeGrandParent = rbNode->getParent()->getParent();
      //recolor(rbNodeGrandParent);
      rbNodeGrandParent->setColor(red);
      rbNode->getParent()->setColor(black);
      rbNodeUncle->setColor(black);
      // now start fixing from grand parent.
      return fixtree(rbNodeGrandParent);
    }
    // Below: either uncle does not exist OR uncle and parent have different color.
    // Case 2: AmIaRightChild==true, rotate left
    RedBlackNode<KeyType, ValueType>   *rbNodeParent = rbNode->getParent();
    if (AmIaRightChild(rbNode) == true)
    {
      LeftRotate(rbNodeParent);
      //return fixtree(rbNodeParent);
      return fixtree(rbNode);
    }
    // Case 3: AmIaLeftChild==true, rotate right
    if (AmIaLeftChild(rbNode) == true)
    {
      RightRotateAndRecolor(rbNodeParent);
      //return fixtree(rbNodeParent);
      return fixtree(rbNode);
    }
  }
} // fixtree

template <class KeyType, class ValueType>
RedBlackNode<KeyType, ValueType> *RedBlackTree<KeyType, ValueType>::findMyUncle(RedBlackNode<KeyType, ValueType> *rbNode)
{
  if (rbNode != NULL && rbNode->getParent() != NULL && rbNode->getParent()->getParent() != NULL)
  {
    if (AmIaRightChild(rbNode->getParent()))
      return rbNode->getParent()->getParent()->getLeft();
    else
      return rbNode->getParent()->getParent()->getRight();    
  }  
  return NULL;
} // findMyUncle

template <class KeyType, class ValueType>
bool RedBlackTree<KeyType, ValueType>::AmIaRightChild(RedBlackNode<KeyType, ValueType> *rbNode)
{
  if (rbNode != NULL && rbNode->getParent() != NULL && rbNode->getParent()->getRight() != NULL && rbNode->getParent()->getRight()->getKey() == rbNode->getKey())
     return true;
  return false;
}//AmIaRightChild

template <class KeyType, class ValueType>
bool RedBlackTree<KeyType, ValueType>::AmIaLeftChild(RedBlackNode<KeyType, ValueType> *rbNode)
{
  if (rbNode != NULL && rbNode->getParent() != NULL && rbNode->getParent()->getLeft() != NULL  && rbNode->getParent()->getLeft()->getKey() == rbNode->getKey())
     return true;
  return false;
} // AmIaLeftChild

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::RightRotateAndRecolor(RedBlackNode<KeyType, ValueType> *rbNode)
{
  // Take the left child, make it the parent and make the original parent the new right child
  RedBlackNode<KeyType, ValueType> *rbNodeLeftChild = rbNode->getLeft();
  RedBlackNode<KeyType, ValueType> *rbNodeRightGrandChild = rbNodeLeftChild->getRight();

  if (rbNode->getParent() == NULL)
    root = rbNodeLeftChild;
  else if (AmIaRightChild(rbNode)==true)
    rbNode->getParent()->setRight(rbNodeLeftChild);
  else
    rbNode->getParent()->setLeft(rbNodeLeftChild);
    
  rbNodeLeftChild->setParent(rbNode->getParent());
  
  rbNode->setParent(rbNodeLeftChild);
  rbNodeLeftChild->setRight(rbNode);
  rbNode->setLeft(rbNodeRightGrandChild);
  if (rbNodeRightGrandChild != NULL)
    rbNodeRightGrandChild->setParent(rbNode);
  rbNode->toggleColor();
  rbNode->toggleColor();
  
} // RightRotate

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::LeftRotate(RedBlackNode<KeyType, ValueType> *rbNode)
{
  // Take the right child, make it the parent and make the original parent the new left child.
  RedBlackNode<KeyType, ValueType> *rbNodeRightChild = rbNode->getRight();
  if (rbNodeRightChild != NULL)
  {
    RedBlackNode<KeyType, ValueType> *rbNodeLeftGrandChild = rbNodeRightChild->getLeft();
    
    if (rbNode->getParent() == NULL)
      root = rbNodeRightChild;
    else if (AmIaRightChild(rbNode)==true)
      rbNode->getParent()->setRight(rbNodeRightChild);
    else
      rbNode->getParent()->setLeft(rbNodeRightChild);
    rbNodeRightChild->setParent(rbNode->getParent());
    rbNode->setParent(rbNodeRightChild);
    rbNodeRightChild->setLeft(rbNode);
    rbNode->setRight(rbNodeLeftGrandChild);
    if (rbNodeLeftGrandChild != NULL)
      rbNodeLeftGrandChild->setParent(rbNode);
  }
} // LeftRotate

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::printrbtree(RedBlackNode<KeyType, ValueType> *r)
{
    if (r != NULL)
	  {
	    std::cout << "[";
	    printrbtree (r->getLeft());
	    std::cout << " (" << r->getKey() << ", " << r->getValue() << "," << r->getColor() << ") ";
    		printrbtree (r->getRight());
    		std::cout << "]";
	  }
}
