#include <iostream>
#include "alistimpls.h"

using namespace std;

int main ( ){
	DoublingArrayList<int> doubling;
  

	PlusTenArrayList<int> plusTen;
	PlusOneArrayList<int> plusOne;
	
	int value;
	//int index;
	
	value=55;
	doubling.push_back (value);
	doubling.push_back (value);
	doubling.push_back (value);
	doubling.push_back (value);
	doubling.print( );
	int size= doubling.size();
	cout<<"size of doubling is: "<<size<<endl;
	cout<<"That was doubling array list."<<endl;
	
	value=75;
	plusOne.push_back (value);
	plusOne.push_back (value);
	plusOne.push_back (value);
	plusOne.push_back (value);
	plusOne.print();
	int size_1= plusOne.size();
	cout<<"Size of plus one is: "<<size_1<<endl;
	cout<<"That was plus one."<<endl;
	
	value=85;
	plusTen.push_back (value);
	plusTen.push_back (value);
	plusTen.push_back (value);
	plusTen.push_back (value);
	plusTen.print ();
	int size_10=plusTen.size();
	cout<<"size of plus ten is : "<<size_10<<endl;
	cout<<"that was the last array left."<<endl;
	

/*	
	arrayList<int> random;
	int tester=60;
	int index=0;
	
	random.push_back (tester);
	random.print();
	//random.insert (index, tester);
	//random.print();
	
	tester=100;
	index=1;
	random.push_back (tester);
	random.print();
	random.insert (index, tester);
	random.print();
	random.remove (index);
	random.print();
	index=0;
	random.set (index, tester);
	random.print();
*/

return 0;
}