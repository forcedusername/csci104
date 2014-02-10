#include <iostream>
#include "hw3q3v3.h"
using namespace std;
	
int main ( ){
	Item<int> item;
	List<int> *pListInt = new List<int>();
	int val;
  try{
	val=10;
    pListInt->insert(-1,val);
    pListInt->insert(0,val);
    pListInt->print ( );
    val=20;
    pListInt->insert(0,val);
    pListInt->print ( );
    val=50;
    pListInt->insert(0,val);
    pListInt->print();
    pListInt->remove(0);
    pListInt->print();
    val=100;
    pListInt->insert (1, val);
    pListInt->print ( );
    val=200;
    pListInt->set(2,val);
    pListInt->print();
    int valret = pListInt->get(0);
    cout<<"get for position 0 val = " << valret << endl;
  
    int sz = pListInt->size();
    valret = pListInt->get(sz);
  }
  catch (int &position)
  {
    cout << "position exception for get at " << position << endl;
  }
 
   return 0;
}//end of main







