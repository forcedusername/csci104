#ifndef alistimpls
#define alistimpls

#include "alist.h"
#include <iostream>

using namespace std;

template <class T>
class DoublingArrayList : public arrayList <T> {
	
	public:
		DoublingArrayList ( ) {};
		~DoublingArrayList ( ){
			delete [ ] array_locate;
		}
	
	protected: 
		using arrayList<T>::resize;
		using arrayList<T>::array_locate;
		using arrayList<T>::current_size;
		using arrayList<T>::capacity;
		void resize ( );
};

template <class T> 
void DoublingArrayList<T>::resize ( ){
  
	T *array_copy=array_locate;
  
	array_locate=new T [capacity*2];
	int z=0;
	while (z<capacity){
		array_locate [z]=array_copy [z];
		z++;
	}
	capacity=capacity*2;
	cout<<"Doubling capacity is: "<<capacity<<endl;
	
	delete [ ] array_copy;

}

template<class T>
class PlusOneArrayList : public arrayList<T>{
	
	public:
		PlusOneArrayList ( ) { };
		~PlusOneArrayList ( ){ 
			delete [ ] array_locate;
		}
	
	protected:
		using arrayList<T>::resize;
		using arrayList<T>::array_locate;
		using arrayList<T>::current_size;
		using arrayList<T>::capacity;
		void resize( );
};


template <class T>
void PlusOneArrayList<T>::resize ( ){
	
	T* array_copy=array_locate;
	array_locate=new T [capacity+1];
	int z=0;
	while (z<capacity){
		array_locate [z]=array_copy [z];
		z++;
	}
	capacity=capacity+1;
	//cout<<"plus one capacity is: "<<capacity<<endl;
	
	delete [ ] array_copy;
}


template <class T>
class PlusTenArrayList : public arrayList <T>{
	
	public:
		PlusTenArrayList ( ){ };
		~PlusTenArrayList ( ){
			delete [ ] array_locate;
		}
	
	protected:
		using arrayList<T>::resize;
		using arrayList<T>::array_locate;
		using arrayList<T>::current_size;
		using arrayList<T>::capacity;
		void resize ( );
};

template <class T>
void PlusTenArrayList<T>::resize ( ){
	T* array_copy=array_locate;
	
	array_locate=new T [capacity+10];
	int z=0;
	while (z<capacity){
		array_locate [z]=array_copy [z];
		z++;
	}
	capacity=capacity+10;
	//cout<<"plus ten capacity is: "<<capacity<<endl;
	
	delete [ ] array_copy;
}

#endif
