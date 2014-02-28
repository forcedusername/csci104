// necessary includes can go here
#ifndef _Map
#define _Map

#include "listv2.h"

template<class keyType, class valueType>
class Pair {
public:
	keyType key;
	valueType value;
};

template <class keyType, class valueType>
class Map
{
  public:
    Map ();  // constructor for a new empty map

    ~Map () { }; // destructor

    int size () const; // returns the number of key-value pairs

    void add (const keyType & key, const valueType & value); 
      /* Adds a new association between the given key and the given value.
         If the key already has an association, it should throw an exception.
      */

    void remove (const keyType & key);
     /* Removes the association for the given key.
        If the key has no association, it should throw an exception. */

    valueType& get (const keyType & key) const;
     /* Returns the value associated with the given key.
        If the key has no association, it should throw an exception. */
     

  private:
    List<Pair<keyType, valueType> > internalstorage;
     /* You should store all of your associations inside one list.
        It is part of your assignment to figure out what types you 
        should store in that list.
        (Hint: you may need to add an additional definition.) */

     /* If you like, you can add further data fields and private
        helper methods.
        In particular, a 'find' function could be useful, which
        will find the index in the list at which a given key sits. */
    int find (const keyType &key) const;
};

template <class keyType, class valueType>
Map <keyType, valueType>::Map ( ){//: keyType (NULL), valueType (NULL) {
  
};
//how do i make a list in this map? 
template <class keyType, class valueType>
void Map <keyType, valueType>::add (const keyType & key, const valueType & value){
	int pos = find (key);
	if (pos!=-1){
		throw pos;
	}
	Pair<keyType,valueType> *pPair = new Pair<keyType,valueType>();
	pPair->key = key;
	pPair->value = value;
	internalstorage.insert (0, *pPair);
}

template <class keyType, class valueType>
void Map <keyType, valueType>::remove (const keyType & key){
	int pos =find (key);
	if (pos==-1){
		throw pos; //that means you cant delete a nonexisent key
	}
  
	internalstorage.remove (pos);
}
template <class keyType, class valueType>
int Map <keyType, valueType>::find (const keyType& key) const{
  //ill call the get function which returns type T
  //returns an item of the list
  //which means what exactly
  //it means that you will keep comparing the items in the map
  //with the key until you find one
  //when you do you return i
	int size_list= internalstorage.size ( );
	Pair<keyType, valueType> keypair;
	for (int i=0;i<size_list;i++){
		keypair=internalstorage.get (i);
		if (keypair.key==key){
			return i;
		}
	}
	return -1; //this means you didnt find it
}

template <class keyType, class valueType>
valueType& Map <keyType, valueType>::get (const keyType & key) const{
	//so what does get do? get just find a key value pair so a data type Pair
  
  //Pair <keyType, valueType> reception;
	int get_parameter;
	get_parameter= find (key);
	if (get_parameter==-1) {
		throw get_parameter;
	}
	return internalstorage.get (get_parameter).value;
  //return reception.value;
}

#endif
