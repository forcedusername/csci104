// necessary includes can go here
#ifndef _List
#define _List
#include <cstring>
#include <iostream>
using namespace std;

template <class T>
struct Item
{
  T value;
  Item<T> *prev, *next;
};

template <class T>
class List
{
  public:
    List();   // constructor

    ~List () { cleanup();};  // destructor

    int size () const;  // returns the number of elements in the list

    void insert (int position, const T & val);
      /* Inserts val into the list before the given position,
         shifting all later items one position to the right.
         Inserting before 0 makes it the new first element.
         Inserting before size() makes it the new last element.
         Your function should throw an exception if position is
         outside the legal range. */

    void remove (int position);
      /* Removes the item from the given position, shifting all
         later items one position to the left.
         Your function should throw an exception if position is
         outside the legal range. */

    void set (int position, const T & val);
      /* Overwrites the given position with the given value.
         Does not affect any other positions.  
         Your function should throw an exception if position is
         outside the legal range. */

    T& get (int position) const;
      /* Returns the item at the given position.
         Your function should throw an exception if position is
         outside the legal range. */
    void print() const;
    private:
      Item<T> *head;
	  Item<T> *tail;
    void cleanup();
      /* You may add further private data fields or helper methods if 
         you choose. You should not alter the public signature. */
};
template <class T>
List <T>::List(): head(NULL),tail(NULL) {};
template <class T>
void List <T>::cleanup()
{
  // walk through and remove all the items.
}

template <class T>
void List <T>::insert (int position, const T &val){
	//cout<<"Entering."<<endl;
	if (position < 0||position> size()){
		//how do you throw a bloody exception
		cout<<"Illegal check"<<endl;
		throw position;
	}
	
	Item<T>* add_in= new Item<T>;
  add_in->next = NULL;
  add_in->prev = NULL;
	add_in->value= val;
	if (head==NULL){
		head=add_in;
		tail=add_in;
		return;
	}
	
	if (position==0){
		//push front operation
		add_in->next=head;
		head->prev=add_in;
		add_in->prev=NULL;
		head=add_in;
		return;
	}
	else if (position == size()){
		add_in->next=NULL;
		add_in->prev=tail;
		tail->next=add_in;
		tail=add_in;
		return;
	}
		
	else {
		//you'll have to find element at this position? how would you do that
		//you use head a copy of head and walk down
		Item<T>* head_copy =head;
		for (int i=0; i<position;i++){
			head_copy=head_copy->next;
			//head_copy is at the index before the specified position
		}
    head_copy->prev->next=add_in;
    add_in->prev=head_copy->prev;
    add_in->next=head_copy;
    head_copy->prev=add_in;
		return;
		//head_copy=add_in;
	}
	
}

template <class T>
void List <T>:: remove (int position){
	Item<T>* head_copy =head;
	Item<T>* deletion;
  if (position >= size())
    throw position;
    
		for (int i=0; i<position;i++){
			head_copy=head_copy->next;
			//you arent deleting head_copy, only the next one
		}
		
	deletion=head_copy;
  if (deletion->prev != NULL)
  {
    // NOT the first item in the list being removed.
    deletion->prev->next=deletion->next;
  }
  else 
  {
    // first item list being removed.
    head = deletion->next;
  }
  if (deletion->next != NULL)
  {
    // NOT the last item in the list being removed.
    deletion->next->prev = deletion->prev;
  }
  else
  {
    // last item in the list is being removed.
    tail = deletion->prev;
  }
	
	delete deletion;
	return;
}

template <class T>
void List <T>:: set (int position, const T &val){
	Item<T>* head_copy=head;
  if (position <0 || position >= size())
    throw position;
		for (int i=0; i<position;i++){
			head_copy=head_copy->next;
		}
	head_copy->value=val; 
	return;
}

template <class T>
T& List<T>:: get (int position) const{
	Item<T>* head_copy =head;
  if (position <0 || position >= size())
		throw position;
  for (int i=0; i<position;i++){
			head_copy=head_copy->next;
	}
		return head_copy->value;
}
template <class T>
int List <T>:: size() const {
	Item<T> *head_copy = head;
	if (head == NULL){
		return 0;
	}
	int sz = 0;
	while(head_copy != NULL){
		sz++;
		head_copy = head_copy->next;
	}
	return sz;
}

template <class T>
void List <T>::print() const {
	Item<T> *head_copy = head;
	if (head_copy == NULL)
		return;
	int pos = 0;
	while(head_copy != NULL){
		cout << "position : " << pos << " ; value : " << head_copy->value <<endl;
		pos++;
		head_copy = head_copy->next;
	}
	return;
}

#endif
