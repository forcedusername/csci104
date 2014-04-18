#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "stdio.h"
#include "Heap.h"

using namespace std;

int main (int argc, char* argv[]){
	Comparator <int> comp;	
	
	if (argc != 3){
		cout << "Usage: Executable, Number of Elements, d children" << endl;
		return 0;
	}

	srand (time (NULL));
	unsigned int d;
	d= atoi (argv[2]);
		
	vector <MaxHeap<int, Comparator<int> > > heap_vec;
	vector <int> place;
	unsigned int numElements;
	
	numElements = atoi(argv[1]);
	double teatime, next=0.0000000;
	
	clock_t start1,end1, start2, end2;
	start1=clock();
	
	for (int x=0; x<10; x++){
		MaxHeap<int, Comparator<int> > dary (d, comp);
		for (unsigned int i=0; i<numElements; i++){
			int random= rand()%10000;
			place.push_back (random);
		}
		for (unsigned int t=0; t<place.size();t++){
			dary.add (place[t]);
		}
		heap_vec.push_back (dary);
	}
	end2=clock();
	teatime=double(start1);
	next= double (end2);
	double fin_time= next-teatime;
	fin_time=fin_time/10;
	//cout<<"Fin_time is: "<<fin_time;
	
	double tea = 0.000000000000;
	//double teatime;
	double naught=0.000000000;
	
	start2=clock();
    
	for (unsigned int g=0; g<heap_vec.size(); g++){
		MaxHeap<int, Comparator <int> > temp (d, comp);
		temp=heap_vec[g];
		temp.remove();
	}
	
	end1= clock();
	tea= (double)start2;
	//double next=0.00000000000;
	
	naught = (double) end1;
	
	double last_time= naught-tea;
	last_time=last_time/10;
	/*
	cout<<"Naught is: "<<naught<<endl;
	cout<<"tea is: "<<tea<<endl;
	cout<<"last time is: "<<last_time<<endl;
*/

return 0;
}