#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
//#include "int_str.h"

using namespace std;

struct int_str{
	int grade; 
	string name;
};

int random_value (int end);

//for soritng filed data
bool is_sorted (vector<int_str> &list);
void swap (vector <int_str> &list, int first, int second);
int get_partition (vector<int_str> &list, int start, int end);
void qrand (vector <int_str> &list, int start, int end);

//for sorting the grades possible to assign
bool is_sorted (vector<int> &list);
void swap (vector <int> &list, int first, int second);
int get_partition (vector<int> &list, int start, int end);
void qrand (vector <int> &list, int start, int end);


int main (int argc, char* argv[]){
	if (argc <3){
		cout<<"Executable, filename, outputfilename..."<<endl;
		cout<<"Exiting program."<<endl;
		return 0;
	}
	
	ifstream input (argv[1]);
	string line;
	vector <string> file;
	while (getline (input, line)){
		file.push_back (line);
	}
	
	vector <int_str> name_grades;
	//vector <string> names;
	vector <int> scores;
	//vector <int> num_grade;
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
		
		//this is where you get the names and num grades
		int_str member;
		for (unsigned int g=0; g<temp.size(); g++){
			if (temp [g]==' '){
				string sub= temp.substr (0,g);
				//cout<<"Sub is: "<<sub<<endl;
						
				string num_score= temp.substr (g+1);
				//cout<<"Num score is: "<<num_score<<endl;
				
				member.name=sub;
				//names.push_back (sub);
				int insert= atoi (num_score.c_str());
				member.grade=insert;
				
				//num_grade.push_back(insert);
				name_grades.push_back (member);
				
				break;
			}
		}
	}
	//all scores have been attained
	
	qrand (name_grades, 0 , name_grades.size()-1);
	qrand (scores, 0, scores.size()-1);
	
	int w=0;
	unsigned int ff=0;
	bool malform = false;
	while (ff<scores.size()){
		if (scores[ff]>=name_grades[w].grade){
			name_grades[w].grade=scores[ff];
			scores[ff]=0;
			w++;
			ff++;
		}
		//what if you have not enough grades/not possible to assign these grades ... 
		//do you even need this check... you order the items already
		//if you ever have to skip you know you'll run out of grades
		else {
			//cout<<"Malformed gradebook. "<<endl;
			malform=true;
			break;
		}
	}
	
	//string output_file (argv [2]);
	ofstream writer (argv[2]);
	//map<string, WebPage*>::iterator printing=pageMap.begin();
	if (malform==true){
		writer<<"impossible to assign grades according to specifications."<<endl;
	}
	else {
		for (unsigned int ness=0; ness<name_grades.size();ness++){
			writer<<name_grades[ness].name<<' '<<name_grades [ness].grade<<endl;
		}
	}
	writer.close();
	
return 0;
}

void qrand (vector<int_str> &list, int start, int end){
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
		cout<<list [i].grade<<endl;
		cout<<list [i].name<<endl;
	}
	cout<<endl;
	*/
	
	qrand (list, start, location);
	qrand (list, location+1, end);
}

bool is_sorted(vector<int_str> &list){
	bool sorted=true;
	for (unsigned int i=0; i<list.size()-1; i++){
		if (list [i].grade>list[i+1].grade){
			sorted=false;
		}
	}
	return sorted;
}

void swap (vector <int_str> &list, int first, int second){
	int_str temp;
	int_str temp1;
	temp.name=list[first].name;
	temp.grade=list[first].grade;
	
	temp1.name=list [second].name;
	temp1.grade=list [second].grade;
	
	list [first].name=temp1.name;
	list [first].grade=temp1.grade;
	
	list [second].name=temp.name;
	list [second].grade=temp.grade;
	/*
	int_str temp= list [first];
	int_str temp_place=list [second];
	list[first]=temp_place;
	list[second]=temp;
	*/
}


int random_value (int start, int end){
	int partition= (rand ()% (end-start)) + start ;
	//cout<<"random value selected is: "<<partition<<endl;
	return partition;
}

int get_partition (vector<int_str> &list, int start, int end){
	int part=random_value (start, end);
	//cout<<"partition index is: "<<part<<endl;
	
	int switching_val= list [part].grade;
	//cout<<"value at partition index is: "<<list [part]<<endl;
	swap (list, part, end);
	
	int left= start;  
	int right= end-1;
	//right is the right most index after the partition
	//left is starting index
	//cout<<list [right]<<" is list [right] before while loop"<<endl;
	while (left<right){
		while (list [left].grade<=switching_val && left<right){
			left++;
		}
		while (list [right].grade>=switching_val && right>left){
			right--;
		}
		
		if (left<right){
			swap (list, right, left);//[right], list[left]);
		}
	}
	if (list [right].grade>list [end].grade){
		swap (list, right , end);//[right], list[end]);
	}
	//so you swap the right with the end again
	//cout<< list [right]<<" is list [right] after the swap"<<endl;
	return right;
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
