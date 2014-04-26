#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
//#include <deque>
//#include "itemitemint_str.h"

using namespace std;

struct itemint_str{
	itemint_str* prev;
	itemint_str* next;
	int grade; 
	string name;
	string teammate;
};

int hash (itemint_str** hash_table, itemint_str &key);


int main (int argc, char* argv[]){
	if (argc <2){
		cout<<"Executable, filename"<<endl;
		cout<<"Exiting program."<<endl;
		return 0;
	}
	
	ifstream input (argv[1]);
	string line;
	vector <string> file;
	while (getline (input, line)){
		file.push_back (line);
	}
	
	vector <itemint_str> name_grades;
	//vector <string> names;
	vector <int> scores;
	//vector <int> num_grade;
	string grade;
	
	//file processing
	int total=0;
	for (unsigned int i=1; i<file.size();i++){
		string temp= file [i];
		
		/*
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
		*/
		
		//this is where you get the names and num grades
		itemint_str member;
		for (unsigned int g=0; g<temp.size(); g++){
			if (temp [g]==' '){
				string sub= temp.substr (0,g);
				//cout<<"Sub is: "<<sub<<endl;
						
				string num_score= temp.substr (g+1);
				//cout<<"Num score is: "<<num_score<<endl;
				
				member.name=sub;
				//names.push_back (sub);
				int insert= atoi (num_score.c_str());
				total+=insert;
				
				member.grade=insert;
				
				//num_grade.push_back(insert);
				name_grades.push_back (member);
				
				break;
			}
		}
	}
	//all scores have been attained
	
	//hash table
	itemint_str* hash_table [17];
	for (int i=0; i<17; i++){
		// [i]->prev=NULL;
		hash_table [i]=NULL;
	}
	
	vector <int> keys;
	for (unsigned int i=0; i<name_grades.size();i++){
		keys.push_back (hash (hash_table, name_grades [i]));
	}
	/* 
	//debugging to check if hash function worked properly
	for (int i=0; i<17;i++){
		if (hash_table [i]==NULL){
			cout<<"not assigned."<<endl;
			continue;
		}
		
		while (hash_table [i]->next!=NULL){
			cout<<"Keys and names at "<<i<<" are: "<<hash_table [i]->name<<endl;
			hash_table [i]=hash_table [i]->next;
		}
		cout<<"Keys and names are: "<<hash_table [i]->name<<endl;
	}
	 */
	//amount of teams
	int teams= name_grades.size()/2;
	
	if (total%teams>0){
		cout<<"No possible teams of two."<<endl;
		return 0;
	}
	
	total=total/teams;
	//double fin_total= total/teams;
	//to make teams
	
	for (unsigned int i=0; i<name_grades.size();i++){
	//you store all the hash table keys in keys
	//how will you get the sum? of all the possible pairs
	//you could go and hop around
	//account for hash table 
		unsigned int j=i+1;
		
		//multiple entries in index
		if (hash_table [keys [i]]->next!=NULL){
			int z=i;
			unsigned int f=j;
			
			//you're in the chain
			while (hash_table [keys [z]]->next!=NULL){
				while ((hash_table [keys [z]]->grade+hash_table [keys [f]]->grade)!=total&&hash_table [keys [z]]->teammate.empty()){
					f++;
					if (f==name_grades.size()){
						cout<<"No fair pairings."<<endl;
						return 0;
					}
				}
				hash_table [keys [z]]=hash_table [keys [z]]->next;
			}
			
			if (hash_table [keys [z]]->teammate.empty()&&hash_table [keys [f]]->teammate.empty()){
				hash_table [keys [z]]->teammate=hash_table [keys [f]]->name;
				cout<<hash_table [keys [z]]->name<<' '<<hash_table [keys [z]]->teammate<<endl;
			}
			
			else {
				cout<<hash_table [keys [z]]->name<<' '<<hash_table [keys [z]]->teammate<<endl;
			}
		}
		
		//single entries in index
		else {	
			while ((hash_table [keys [i]]->grade+hash_table [keys [j]]->grade)!=total&&hash_table [keys[i]]->teammate.empty()){
				j++;
				if (j==name_grades.size()){
					cout<<"No fair team pairings exist."<<endl;
					return 0;
				}
				//j++;
			}
		
		//team pairing does exist...
			if (hash_table [keys [i]]->teammate.empty()&&hash_table [keys [j]]->teammate.empty()){
				hash_table [keys[i]]->teammate= hash_table [keys[j]]->name;
				hash_table [keys[j]]->teammate= hash_table [keys[i]]->name;
				cout<<hash_table [keys[i]]->name<<' '<<hash_table [keys [i]]->teammate<<endl;
			}
		
		//if you've already been assigned
			else {
				cout<<hash_table [keys[i]]->name<<' '<<hash_table [keys [i]]->teammate<<endl;
			}
		
		}
	}
	return 0;
}

int hash (itemint_str** hash_table, itemint_str &key){
	//here you're going to give indices to all the name_grade structs
	int num1= key.name.length();
	int num2= key.grade;
	int index= num1*num2%17;
	//cout<<"assigned index is: "<<index<<endl;
	
	//first item in hash list
	if (hash_table [index]==NULL){
		hash_table [index]=&key;
		key.prev=hash_table[index];
		key.next=NULL;
	}
	
	else {
		key.next=hash_table [index];
		hash_table [index]->prev=&key;
		hash_table [index]=&key;
		key.prev=hash_table [index];
	}
	
	return index;
}