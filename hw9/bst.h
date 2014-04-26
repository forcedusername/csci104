/*
 * bst.h
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe and redekopp
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Exceptions
 ------------------------------------------------------*/

class KeyNotFoundException : public std::exception
{ // thrown when the user searches for a non-existing key
public:
   	KeyNotFoundException () throw () {}
	~KeyNotFoundException () throw () {}
};

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

 
 
template <class KeyType, class ValueType>
class Node {
public:
	Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
        // the default is to create new nodes as leaves
	{ _item.first = k; _item.second = v; _parent = p; _left = _right = NULL; }

	const std::pair<KeyType, ValueType> & getItem () const
	{ return _item; }

	//	std::pair<KeyType, ValueType> & getItem ()
	//	{ Return; }

	const KeyType & getKey () const
	{ return _item.first; }

	const ValueType & getValue () const
	{ return _item.second; }

        /* the next three functions are virtual because for Red-Black-Trees,
           we'll want to use Red-Black nodes, and for those, the 
           getParent, getLeft, and getRight functions should return 
           Red-Black nodes, not just ordinary nodes.
           That's an advantage of using getters/setters rather than a struct. */

	virtual Node<KeyType, ValueType> *getParent () const
	{ return _parent; }

	virtual Node<KeyType, ValueType> *getLeft () const
	{ return _left; }

	virtual Node<KeyType, ValueType> *getRight () const
	{ return _right; }


	void setParent (Node<KeyType, ValueType> *p)
	{ _parent = p; }

	void setLeft (Node<KeyType, ValueType> *l)
	{ _left = l; }

	void setRight (Node<KeyType, ValueType> *r)
	{ _right = r; }
	
	//if you want to overwrite a key
	void setValue (ValueType val){
		_item.second=val;
	}

	virtual ~Node ()
	{ }
	
	//is this necessary/what do you do
//	bool operator < (Node<KeyType, ValueType>* lhs, Node<KeyType, ValueType>* rhs){
	bool operator < (Node<KeyType, ValueType>* rhs){
		if (this->getKey()<rhs->getKey()){
			return true;
		}
		else {
			return false; 
		}
	}

protected:
	std::pair<KeyType, ValueType> _item;
	Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
public:
	BinarySearchTree () { root = NULL; }
	~BinarySearchTree () { deleteAll (root); }

	const ValueType & lookup (const KeyType & k) const{
	  /* you need to implement the lookup function.
             It should throw a KeyNotFoundException if k is not in the tree.
             You are allowed/encouraged to create private helper functions.	     
    */	
    Node<KeyType, ValueType> *currNode = root;
    while (currNode != NULL)
    {
      if (currNode->getKey() == k)
      {
        return currNode->getValue();
      }
      else if (currNode->getKey() > k)
      {
        if (currNode->getLeft() == NULL)
        {
          throw KeyNotFoundException();
        }
        currNode = currNode->getLeft();        
      }
      else
      {
        if (currNode->getRight() == NULL)
        {
          throw KeyNotFoundException();
        }
        currNode = currNode->getRight();        
      }
    }
    throw KeyNotFoundException();
	} // lookup
	
	void print () const
	{ 
	//prints the entire tree structure in a nice format, denoting subtrees in [] brackets.
	//This could be helpful if you want to debug your functions.
	     printRoot (root);
	     std::cout << "\n";
	}

  void makeTestBST(Node<KeyType,ValueType> *rootTest) {
      root=rootTest;
  }
	/*-------------------------------------
         * An In-Order Const iterator
	 *-------------------------------------*/
	class iterator {
	public:
	  iterator(Node<KeyType,ValueType>* root) 
	  {
	      curr = root;
			if(curr){
				while(curr->getLeft()){
					curr = curr->getLeft();
				}
			}
	  }

		const std::pair<KeyType,ValueType>& operator*() const
			{ return curr->getItem(); }

		const std::pair<KeyType,ValueType>* operator->() const
			{ return &(curr->getItem()); }

		bool operator==(const iterator& rhs) const
		{
			return curr == rhs.curr; 
		}

		bool operator!=(const iterator& rhs) const
		{
			return curr != rhs.curr;
		}

		iterator& operator++(){
			//is root already part of the iterator 
			successor();
      return *this;
		}	
	  // this one is yours to implement
	  
	protected:
		Node<KeyType, ValueType>* curr;
    
    void successor() {
      if (curr == NULL)
        return;
    
      // if non-null right child, then step down to right and then go left as much as you can
      if (curr->getRight() != NULL)
      {
        curr = curr->getRight();
        while (curr->getLeft() != NULL)
        {
          curr = curr->getLeft();
        }
        return;
      }
      else
      {
        // we can't go right and we need to go back up, go back up through right until we HAVE to navigate 
        // through left link.
        Node<KeyType, ValueType>* parent = curr->getParent();
        while (parent != NULL && parent->getRight() == curr)
        {
          curr = parent;
          parent = curr->getParent();
        }
        curr = parent;
      }
      
    } // successor
      
	};

	iterator begin() { iterator it (root); return it; }
	iterator end()   { iterator it (NULL); return it; }

 protected:
	Node<KeyType, ValueType> *root;

	void printRoot (Node<KeyType, ValueType> *r) const
	{
    	if (r != NULL)
	  {
	    std::cout << "[";
	    printRoot (r->getLeft());
	    std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
    		printRoot (r->getRight());
    		std::cout << "]";
	  }
	}

	void deleteAll (Node<KeyType, ValueType> *r)
	{
	  if (r != NULL)
	    {
	      deleteAll (r->getLeft());
	      deleteAll (r->getRight());
	      delete r;
	    }
	}
};

