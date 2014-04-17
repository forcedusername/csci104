#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

bool is_sorted (vector<int> &list);
void swap (vector <int> &list, int first, int second);
int random_value (int end);
int get_partition (vector<int> &list, int start, int end);
void qrand (vector <int> &list, int start, int end);

int main (int argc, char* argv[]){
	if (argc <2){
		cout<<"Executable, filename..."<<endl;
		cout<<"Exiting program."<<endl;
		return 0;
	}
	
	ifstream input (argv[1]);
	string line;
	vector <string> file;
	while (getline (input, line)){
		file.push_back (line);
	}
	vector <string> names;
	vector <int> scores;
	vector <int> num_grade;
	string grade;
	
	//file processing
	for (unsigned int i=1; i<file.size();i++){
		string temp= file [i];
		//char word_num [temp.size()+1];
		if (temp [i]<'A'){
		//this means it's a number...
			for (unsigned int i=0; i<temp.size(); i++){
				grade [i]=temp [i];
				//cout<<"Num grade is: "<<num_grade [i]<<endl;
			}
			int temp= atoi (grade.c_str());
			scores.push_back (temp);
			grade.clear();
			continue;
		}
		
		for (unsigned int g=0; g<temp.size(); g++){
			if (temp [g]==' '){
				string sub= temp.substr (0,g);
				//cout<<"Sub is: "<<sub<<endl;
						
				string num_score= temp.substr (g+1);
				//cout<<"Num score is: "<<num_score<<endl;
				
				names.push_back (sub);
				int insert= atoi (num_score.c_str());
				num_grade.push_back(insert);
				
				break;
			}
		}
	}
	//you have all the scores now
	
	
	
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
	
	for (unsigned int i=0; i<list.size();i++){
		cout<<list [i]<<' ';
	}
	cout<<endl;
	
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
