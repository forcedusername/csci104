#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include "stdio.h"

using namespace std;

bool is_sorted (vector<int> &list);
void swap (vector <int> &list, int first, int second);
int random_value (int end);
int get_partition (vector<int> &list, int start, int end);
void qrand (vector <int> &list, int start, int end);

int main (int argc, char *argv[] ){
	
	vector<int> place;
	srand (time (NULL));

	if (argc != 3){
		cout << "Usage: Executable, Number of Elements, Number of Swaps." << endl;
		return 0;
	}
	unsigned int numElements;
	unsigned int numSwaps;
  
	numElements = atoi(argv[1]);
	numSwaps    = atoi(argv[2]);
  
	for (unsigned int i=0; i<numElements; i++){
		place.push_back (i);
	}
	for (unsigned int i=0; i<numSwaps; i++){
		int index1 = rand ()%numElements;
		int index2 = rand ()%numElements;
		swap(place,index1,index2);
	}
  /*
	cout<<"before sorting..."<<endl;
	for (unsigned int i=0; i<place.size(); i++){
		cout<<place [i]<<" ";
	}
	cout<<endl;
	*/
	//double teatime = 0.000000000000;
	double teatime;
	double next;
	clock_t start,end;
	start=clock();
    
	qrand (place, 0, place.size()-1);
	
	end= clock();
	teatime= (double)start;
	//double next=0.00000000000;
	
	next = (double) end;
	
	//double fin_time= next-teatime;
	//teatime/=CLOCKS_PER_SEC;
	cout<<"Next is: "<<next<<endl;
	cout<<"teatime is: "<<teatime<<endl;
	//cout<<"fin time is: "<<fin_time<<endl;
	/*
	cout<<"after sorting..."<<endl;
	for (unsigned int i=0; i<place.size(); i++){
		cout<<place [i]<<" ";
	}
	cout<<endl;
	*/
	
return 0;	
}

void qrand (vector<int> &list, int start, int end){
	/*
	bool sorting=is_sorted (list);
	if (sorting==true||start>=end){
		return;
	}
	*/	
	if (start>=end){
		return;
	}

	int location= get_partition (list, start, end);
	//cout<<"get partition returns "<<location<< " (" << start << "," << end << ")" <<endl;
	
	/*
	for (unsigned int i=0; i<list.size();i++){
		cout<<list [i]<<' ';
	}
	cout<<endl;
	*/
	qrand (list, start, location);
	qrand (list, location+1, end);
}

bool is_sorted(vector<int> &list){
	bool sorted=true;
	for (unsigned int i=0; i<list.size()-1; i++){
		if (list [i]>list[i+1]){
			sorted=false;
		}
	}
	return sorted;
}

void swap (vector <int> &list, int first, int second){
	int temp= list [first];
	int temp_place=list [second];
	list[first]=temp_place;
	list[second]=temp;
}


int random_value (int start, int end){
	int partition= (rand ()% (end-start)) + start ;
	//cout<<"random value selected is: "<<partition<<endl;
	return partition;
}

int get_partition (vector<int> &list, int start, int end){
	int part=random_value (start, end);
	//cout<<"partition index is: "<<part<<endl;
	
	int switching_val= list [part];
	//cout<<"value at partition index is: "<<list [part]<<endl;
	swap (list, part, end);
	
	int left= start;  
	int right= end-1;
	//right is the right most index after the partition
	//left is starting index
	//cout<<list [right]<<" is list [right] before while loop"<<endl;
	while (left<right){
		while (list [left]<=switching_val && left<right){
			left++;
		}
		while (list [right]>=switching_val && right>left){
			right--;
		}
		
		if (left<right){
			swap (list, right, left);//[right], list[left]);
		}
	}
	if (list [right]>list [end]){
		swap (list, right , end);//[right], list[end]);
	}
	//so you swap the right with the end again
	//cout<< list [right]<<" is list [right] after the swap"<<endl;
	return right;
}
