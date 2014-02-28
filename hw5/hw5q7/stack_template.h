#include "alistimpls.h"
#include "alist.h"
#include <iostream>

using namespace std;


template <class T>
class Stack : public PlusTenArrayList<T> /* may add inheritance declarations here 
            - decide if inheritance is private or public */
{
	public:
  // add appropriate constructors and destructors
		Stack(){};
		~Stack(){};
		using PlusTenArrayList<T>::isEmpty;
		using PlusTenArrayList<T>::push_back;
		using PlusTenArrayList<T>::remove;
		using PlusTenArrayList<T>::current_size;
		using PlusTenArrayList<T>::capacity;
		//using PlusTenArrayList<T>::array_locate;
    using PlusTenArrayList<T>::get;
		//using PlusTenArrayList<T>::pop( 
		//bool isEmpty() const;
		/* returns whether the stack contains any elements */

		void push(const T& val) {push_back(val); };
		/* adds a value to the top of the stack */
    
		void pop();
		/* deletes the top value from the stack */

		T const & top() const;
		/* returns the top value on the stack */
};

template <class T>
T const&  Stack<T>::top() const{
	int last_index= current_size-1;
	return get (last_index);
}

template <class T>
void Stack<T>::pop ( ) {
	remove (current_size-1);
	//cout<<"Removal successful."<<endl;
}