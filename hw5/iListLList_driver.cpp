#include <iostream>
#include "iListLList.h"

using namespace std;

int main ( ){
	List <int> interfacer;
	
	int value=15;
	interfacer.insert (0, value);
	
	value=16;
	interfacer.insert (0, value);
	
	interfacer.print();
	int gaysize= interfacer.size();
	cout<<gaysize<<endl;
	
	interfacer.remove (0);
	interfacer.print ();
	
	value=200;
	interfacer.insert (0, value);
	
	value=50;
	interfacer.set (0, 50);
	interfacer.print ();
	
	cout<<"done"<<endl;


return 0;
}