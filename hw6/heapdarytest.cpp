#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include "Heap.h"

using namespace std;

int main (int argc, char* argv[]){
	Comparator <int> comp;
	
	MaxHeap<int, Comparator<int> > dary (100, comp);
	//why does this not compile
	
	dary.add (12);
	//cout<<"Adding 12."<<endl;
	dary.add (22);
	//cout<<"Adding 22."<<endl;
	dary.add (45);
	//cout<<"Adding 45."<<endl;
	dary.add (44);
	dary.add (21);
	dary.add (11);
	dary.add (99);
	//for (int i=0; i<500; i++){
	//	dary.add (i);
	//}
	
	//something wrong with add
	int placer= dary.peek();
	cout<<"placer is: "<<placer<<endl;
	//cout<<"Placer should be 45..."<<endl;
	
	dary.remove();
	//cout<<"Should've removed 45"<<endl;
	
	int placing= dary.peek();
	cout<<"Placing is: "<<placing<<endl;
	//cout<<"Should be 22"<<endl;
	
	vector <int> temp= dary.get_vec();
	cout<<"Temp size is: "<<temp.size()<<endl;
	//cout<<"Should be 2"<<endl;
	
	/*
	for (int i=0; i<temp.size(); i++){
		cout<<temp [i]<<endl;
	}
	*/
	bool empty= dary.isEmpty();
	int placers= dary.peek ();
	cout<<"Placer is: "<<placers<<endl;
	
	for (int i=0; i<2; i++){
		dary.remove();
	}
	vector<int>next_temp=dary.get_vec();
	cout<<"next temp size is: "<<next_temp.size()<<endl;
	cout<<dary.peek()<<endl; 
return 0;

}