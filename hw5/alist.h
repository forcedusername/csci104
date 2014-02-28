#ifndef alist
#define alist

#include "ilist.h"

using namespace std;

template <class T>
class arrayList : public IList <T>
{
	public: 
		using IList<T>::insert;
		using IList<T>::get;
		using IList<T>::remove;
		using IList<T>::set;
		using IList<T>::size;
 
		arrayList ( ){
			current_size=0;
			capacity=10;
			//you set the capacity at 50 and then add more/less depending on what is necessary
			array_locate= new T [capacity];
		};
		~arrayList ( ){};
		void insert (int position, const T& value);
		T const& get (int position) const;
		void remove (int position);
		void set (int position, const T& value);
		int size ( ) const ;
		//unsigned int capacity_return () const;
		
		bool isEmpty ( );
		void push_back (const T& value);
		T& get (int position);
		bool pop (const T& value);
		void print ( );
		
		T& operator[] (int position){return get (position);};
		const T& operator[] (int position) const {return get (position);};
		//how do you know which get function is called here? 
		//T& operator= (int position);
		//T& operator== (int position);

	protected: 
		virtual void resize () = 0;
		T* array_locate;
		unsigned int current_size;
		unsigned int capacity;
		//set capacity at beginning 
	
};
/*
template<class T>
T& arrayList::operator= (int position){
	

}

template<class T>
T& arrayList::operator== (int position){


}
*/

template <class T>
void arrayList<T>::push_back (const T&value){
	//make sure to add 1 to size after each push back and compare to capacity
	
	if (current_size==capacity){
		resize();
	}
		
	array_locate [current_size]= value;
	current_size++;		
}

template <class T>
void arrayList<T>::insert (int position, const T&value){
	if (isEmpty()==true){
		push_back (value);
		return;
	}
	
	if (position>current_size){
		throw position;
	}
	
	if (position==current_size){
		push_back (value);
		return;
	}
	
	if (current_size==capacity){
		resize();
	}
	
	current_size++;
	int size_copy=current_size;
	while (size_copy>position){
		array_locate [size_copy]=array_locate [size_copy-1];
		size_copy--;
	}
	array_locate [position]=value;
}

template <class T>
void arrayList<T>::remove (int position){
	
	//int position_copy=position;
	while (position<current_size){
		array_locate [position]=array_locate [position+1];
		position++;
	}
	current_size--;
}

template <class T>
bool arrayList<T>::pop (const T& value){
	
	bool success=false;
	int size_walk=0;
	while (size_walk<current_size){
		if (*array_locate [size_walk]==value){
			pop (size_walk);
			success=true;
			return success;
		}
		size_walk++;
	}
	current_size--;
	return success;
	
}

template <class T>
bool arrayList<T>::isEmpty ( ){
	bool empty= false;
	if (current_size==0){	
		empty=true;
		return empty;
	}
	return empty;
}

template<class T>
void arrayList<T>::set (int position, const T& value){
	if (position>current_size){
		throw position;
	}
	array_locate [position]=value;
}

template<class T>
T const& arrayList<T>::get (int position) const {
	if (position>current_size-1){
		throw position;
	}
	
	return array_locate [position];
}

template <class T>
T & arrayList<T>::get (int position) {
	if (position>current_size-1 ){
		throw position;
	}
	
	return array_locate [position];
}

template <class T>
int arrayList<T>::size( ) const {
	return current_size;
}

template<class T>
void arrayList<T>::print ( ){
	int iterator=0;
	while (iterator<current_size){
		cout<<array_locate [iterator]<<" ";
		iterator++;
	}
	cout<<endl;
}

#endif
