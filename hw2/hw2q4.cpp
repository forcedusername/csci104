#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;
struct Item {
		int val;
		Item* next;
	};

Item* filter (Item* head, Item* header, bool (*f) (int));
Item* gen_list (char* file_name);
bool is_even (int something);
bool is_prime (int something);
bool is_square (int something);

int main (int argc, char* argv [ ]){
	Item* head= NULL;
  if (argc != 3)
  {
    printf("USAGE: <cmd> <file> <A|B|C>\n");
    return 0;
  }
	head= gen_list (argv [1]);
		
	Item* header=NULL;
	Item* returner=NULL;
	
	string commando;
	commando="A";
	
	int compare = commando.compare (argv [2]);
	if (compare==0){
		returner= filter (head, header, &is_even);
	}
	string commander;
	commander= "B";
	
	int compare1= commander.compare(argv [2]);
	if (compare1==0) {
		returner= filter (head, header, &is_square);
	}
	
	string command;
	command = "C";
	int compare2= command.compare(argv [2]); // you apparently have to use string compare because the command line argument
										//is a pointer to chars or a string
	if (compare2==0){
		returner= filter (head, header, &is_prime);
	}
	Item* returner_iterate=NULL;
	returner_iterate=returner; //you dont want to lose the head of your sorted list so you copy it
	while (returner_iterate->next!=NULL){
		cout<<returner->val<<endl;
		returner_iterate=returner_iterate->next;
	}
	
	return 0;

}

Item* gen_list (char* file_name){
	ifstream input (file_name);
	int value;
	Item* head=NULL;
	Item* tail=NULL;
	//you have a tail pointer to essentially link the list together. 
	
	while (!input.fail( )){
		input>>value;
		Item* tempo= new Item;
		tempo->val= value;
		tempo->next=NULL;
		if (head==NULL){
			head=tempo;
		}
		if (tail==NULL){
			tail=tempo;
		} 
    else {
			tail->next=tempo;
		}
		tail=tempo;
	}
	return head;
}

bool is_even (int something) {
	if (something%2==0){
		return true;
	}
	else {
		return false;
	}
}

bool is_prime (int something){
  if (something == 0)
    return false;
  something = abs(something);
	for (int j=1;j<something;j++){
		if (something%j==0 && j!=1){
			return false;
		}
	}
  return true;
}

bool is_square (int something) {
	double square_root= sqrt (something);
	int placer= floor (square_root);
	if (placer==square_root){
		return true;
	}
	else {
		return false; 
	}
}

Item* filter(Item* head, Item* header, bool (*f) (int)){
  Item *returnFilter = NULL;
	//cout<<"Entering your filter."<<endl;
	if (head->next==NULL){
		return header;
	}
	//cout<<"head->val " << head->val <<endl;
	bool good= f (head->val);
	if (good == true){
		Item* newer_item= new Item;
    cout<< head->val <<endl;
			
		newer_item->val= head->val;
		newer_item->next= NULL;
		if (header!=NULL){
			header->next=newer_item;
		}
		returnFilter = filter (head->next, header, f);
    return newer_item;
	}
	else {
		returnFilter = filter (head->next, header, f);
    return returnFilter;
	}
}


