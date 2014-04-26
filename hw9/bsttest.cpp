/*
 * rb_test.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "binarysearchtree.h"

/* -----------------------------------------------------
 * main for testing
 ------------------------------------------------------*/
using namespace std;
 
int main (void)
{
  Node<int,int> *arrNodes[100];

  BinarySearchTree<int, int> *T = new BinarySearchTree<int, int> ();

  // let us make a 15 nodes and connect node8 is root
  
  for (int i=1; i<16;i++)
  {
    Node<int,int> *pNode = new Node<int,int>(i,i,NULL);
    arrNodes[i] = pNode;
  }
  // first tie the leaf nodes
  // 1,2,3
  arrNodes[1]->setParent(arrNodes[2]);
  arrNodes[3]->setParent(arrNodes[2]);
  arrNodes[2]->setLeft  (arrNodes[1]);
  arrNodes[2]->setRight (arrNodes[3]);
  
  // 5,6,7
  arrNodes[5]->setParent(arrNodes[6]);
  arrNodes[7]->setParent(arrNodes[6]);
  arrNodes[6]->setLeft  (arrNodes[5]);
  arrNodes[6]->setRight (arrNodes[7]);
  
  
  // 9,10,11
  arrNodes[9]->setParent(arrNodes[10]);
  arrNodes[11]->setParent(arrNodes[10]);
  arrNodes[10]->setLeft  (arrNodes[9]);
  arrNodes[10]->setRight (arrNodes[11]);
  
  
  // 13,14,15
  arrNodes[13]->setParent(arrNodes[14]);
  arrNodes[15]->setParent(arrNodes[14]);
  arrNodes[14]->setLeft  (arrNodes[13]);
  arrNodes[14]->setRight (arrNodes[15]);
  

  // 2,4,6
  arrNodes[2]->setParent(arrNodes[4]);
  arrNodes[6]->setParent(arrNodes[4]);
  arrNodes[4]->setLeft  (arrNodes[2]);
  arrNodes[4]->setRight (arrNodes[6]);
  
  // 10,12,14
  arrNodes[10]->setParent(arrNodes[12]);
  arrNodes[14]->setParent(arrNodes[12]);
  arrNodes[12]->setLeft  (arrNodes[10]);
  arrNodes[12]->setRight (arrNodes[14]);
  
  // Finally 4,8,12
  arrNodes[4]->setParent(arrNodes[8]);
  arrNodes[12]->setParent(arrNodes[8]);
  arrNodes[8]->setLeft  (arrNodes[4]);
  arrNodes[8]->setRight (arrNodes[12]);

  T->makeTestBST(arrNodes[8]);
  T->print();
  //for (BinarySearchTree<int, int>::iterator it=T->begin();it!=T->end();++it){
//	cout<<"Iterator here is: "<<it->first<<' '<<it->second<<endl;
 // }
  int val;

  try{
	val=T->lookup(10);
  }
  
  catch (...){
	cout<<"Not there...?"<<endl;
	val=-1;
  }
  cout<<"Look up returned: "<<val<<endl;
	try{
		val=T->lookup (13);
	}
	
	catch (...){
		cout<<"Not there?"<<endl;
		val=0;
	}
  cout<<"Val is: "<<val<<endl;
  
  
  
  
  return 0;
}
