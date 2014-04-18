#ifndef _MaxHeap	
#define _MaxHeap

#include <cstdlib>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <exception>
//#include "QuicksortRandom.h"

using namespace std;


template <class T>
class Comparator {
	public:
		bool operator () (T &lhs, T &rhs){
			return lhs<rhs;
		}
};


template <class T, class K>

  class MaxHeap {
     public:
		MaxHeap (int d, K comp);
			//new vector
			//push back things via comparing
		/* Constructor that builds a d-ary Max Heap using the given
          comparator to compare elements and decide which one is
          larger. 
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/
		
		MaxHeap (){ };
		~MaxHeap (){ };

		void add (const T & item);
         /* adds the item to the heap */

		const T & peek () const;
         /* returns the element with maximum priority.
            Throws an exception if the heap is empty. */

		void remove ();
         /* removes the element with maximum priority. */

		bool isEmpty () const;
         /* returns true iff there are no elements on the heap. */
		void swap (int lhs, int rhs);
		int get_degree () {return degree;}
		vector <T> get_vec () {return heap_impl;}
	 private:
		vector <T> heap_impl;
		void heapify (int index);
		int degree;
		K less_great;
  };
  #endif
  
template <class T, class K>
MaxHeap <T, K>::MaxHeap (int d, K comp){
	//how do you init a heap?
	//heapify for days?
	//so each node has d children
	degree=d;
	//heap_impl=vector <T> heap;
	less_great= comp;
}

template <class T, class K>
void MaxHeap<T, K>::add (const T &item){
	//all parents > children in this maxheap
	heap_impl.push_back (item);
	int placer=heap_impl.size()-1;
	//cout<<"Max heap placer is: "<<placer<<endl;
	
	int parent= (placer-1)/degree;
	//cout<<"Max heap parent is: "<<parent<<endl;
	//to create a d-ary tree do you divide by d?
	
	while (parent>=0 && heap_impl [placer]>heap_impl [parent]){
		swap (placer, parent);
		placer=parent;
		parent = (placer-1)/degree;
	}
}
  
template <class T, class K>
const T& MaxHeap<T, K>::peek () const {
  //this is the same as top?
	bool empty= isEmpty();
	if (empty==true){
		throw (out_of_range("Out of range"));
	}
	return heap_impl [0];
}
  
template <class T, class K>
void MaxHeap<T, K>::remove () {
	//this is the same as pop
	bool empty= isEmpty();
	if (empty==true){
		throw (out_of_range("Out of range"));
	}
	//dont erase blindly and shrink everything, you dont want to change the index of everything else
	//so when you delete the top element, you dont just promote what's at index of 1
	//make the [0] equal to the back element of the heap
	//and then delete the back element
	//and then heapify the living shit out of it
	heap_impl [0]=heap_impl.back();
	//cout<<"Heap_impl at zero is: "<<heap_impl [0]<<endl;
	heap_impl.pop_back();
	//heap_impl.erase (heap_impl.begin());
	heapify (0);	
}
  
template <class T, class K>
bool MaxHeap<T, K>::isEmpty () const{
	bool empty=false;
	if (heap_impl.size()==0){
		empty=true;
	}
	return empty;
}
  
template <class T, class K>
void MaxHeap<T, K>::heapify (int index){
//what does this do

	if (index>heap_impl.size()-1){
		return;
	}
	int greatest;
	if ((index*degree+1)>heap_impl.size()-1){
		//cout<<"you're at a leaf."<<endl;
		//cout<<"heap_impl at zero is: "<<heap_impl [0]<<endl;
		
		//this doesn't go into the for loop for the last function...
		//return;
		//you have the for loop so you go through all the leaves to compare with the zero index. 
		
		for (int jj=0; jj<heap_impl.size()-1;jj++){
			//cout<<"entered for loop with : "<<heap_impl [0]<<endl;
			if (heap_impl [0]<heap_impl [jj]){
				//cout<<"Heap at 0: "<<heap_impl [0]<<endl;
				//cout<<"Comparing with : "<<heap_impl [jj]<<endl;
				swap (0, jj);
				//cout<<"heap at zero after swap is: "<<heap_impl [0]<<endl;
				jj=0;
				//heapify (0);
				//can you just swap and heapify on zero again
			}	
		}
		
		return;
		/*
		if (degree>heap_impl.size()){
			greatest=index+1;
		
		//you have this check for what....
		//you have this check because you dont want to get/risk a seg fault
		//how do you know you've reached the last leaf? this thing below
		//dont heapify a leaf...
			if (greatest>heap_impl.size()-1){
				return;
			}
		}
		*/
	//index*d + d--
	
	}
	else {
		greatest=degree*index+1; //setting left child to greatest 
		//int right;
	}
	if ((index*degree+degree<=heap_impl.size()-1)){
		int right= greatest+1;
			right=greatest+1;
		if (heap_impl [greatest]<heap_impl[right]){
			greatest=right;
		}
	}
	if (heap_impl[index]<heap_impl [greatest]){
		//do i need to change the swap function to take T and not just indices? 
		
		swap (greatest, index);
		
		heapify (greatest);
	}

			
}


template <class T, class K>
void MaxHeap <T, K>::swap (int lhs, int rhs){
	T temp= heap_impl [lhs];
	T temp_place = heap_impl [rhs];
			
	heap_impl [lhs]=temp_place;
	heap_impl [rhs]=temp;
}