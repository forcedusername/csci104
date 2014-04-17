#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>

using namespace std;
bool is_sorted (vector<int> &list);
void swap (vector <int> &list, int first, int second);
int get_highest (vector<int> &list);
int get_partition (vector<int> &list, int start, int end);
void qlarge (vector <int> &list, int start, int end);

int main ( ){
	vector<int> place;
	srand (time (NULL));

  if (argc != 3)
  {
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
	
	cout<<endl;
		double teatime;
	double next;
	clock_t start,end;
	start=clock();
    
	qlarge (place, 0, place.size()-1);
	
	end= clock();
	teatime= (double)start;
	//double next=0.00000000000;
	
	next = (double) end;
	
	//double fin_time= next-teatime;
	//teatime/=CLOCKS_PER_SEC;
	cout<<"Next is: "<<next<<endl;
	cout<<"teatime is: "<<teatime<<endl;
	
	//qlarge (place, 0, place.size()-1);
	//measuring time...
	
	return 0;
	
}

void qlarge (vector<int> &list, int start, int end){
	if (start>=end){
		return;
	}
	int location= get_partition (list, start, end);
	//cout<<"Location is: "<<location<<endl;
	
	qlarge (list, start, location);
	qlarge (list, location+1, end);
}

bool is_sorted(vector<int> &list){
	bool sorted=true;
	for (unsigned int i=0; i<list.size()-2; i++){
		if (list [i]>list[i+1]){
			sorted=false;
      break;
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


int get_highest (vector <int> &list){
	int max=0;
	
	unsigned int i=0;
	while (i<list.size()){
		if (list [i]>max){
			max=list[i];
		}
		i++;
	}
	
	unsigned int z=0;
	for (; z<list.size();z++){
		if (list [z]==max){
			//cout<<max<<" is the max value."<<endl;
			//cout<<z<<" is its index"<<endl;
			return z;
		}
	}
	
	return z;
	
}

int get_partition (vector<int> &list, int start, int end){
	//int part=get_highest (list);
  int part = end;
	//cout<<"part is: "<<part<<endl;
	int switching_val= list [part];
	//cout<<"Switching_val is: "<<switching_val<<endl;
	
	int left= start; 
	int right= end-1;
	
	while (left<right){
		while (list [left]<=switching_val && left<right){
			left++;
		}
		while (list [right]>=switching_val && right>left){
			right--;
		}
		
		if (left<right){
			swap (list ,right, left);
		}
	}
	if (list [right]>list [end]){
			swap (list ,right, end);
	}
  
	return right;
}
