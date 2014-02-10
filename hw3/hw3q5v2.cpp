#include "hw3q5v2.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
 
using namespace std;

int main (int argc, char* argv[ ] ) {
	if (argc<2){
		cout<<"enter filename again."<<endl;
		return 0;
	}
	char* filename= argv [1];
	//so with the filename, you have to read in the email addresses
	//that;s the key
	//the names are the values
  
	//so how do you read in from the file? 
	ifstream input (argv[1]);
	vector <string> email_keys;
	vector <string> people_keys;
  
	while (!input.fail( )){
		string email;
		string name;
		string firstname;
		string lastname;
		string fullname;
		int i;
		getline (input, email, ' ');
		char chars [ ]=" '\t', ' '";
		getline (input, name);
    // first trim the front
    for (i=0; i<name.length(); i++){
		if (name[i] != ' ' && name[i] != '\t'){
			break;
		}
    }
    name.erase(0,i);
    // extract first name
    for (i=0; i<name.length(); i++){
		if (name[i] == ' ' || name[i] == '\t'){
			break;
		}
    }
    firstname = name.substr(0, i);
    name.erase(0,i);
    // look for start of last name
    for (i=0; i<name.length(); i++){
		if (name[i] != ' ' && name[i] != '\t'){
			break;
		}
    }
    name.erase(0,i);
    fullname  = firstname + " " + name;
		email_keys.push_back (email);
		people_keys.push_back (fullname);
	}

  	Map<string,string> map;	
	unsigned int sizer = email_keys.size( );
	//how many emails there are is how many pairs there are
	
	int x=0;
	while (x<sizer){
		map.add (email_keys [x], people_keys [x]);
		x++;
	}
	
	string weird_lookup;
	string value;
	while (1){
		cout<<"Please enter an email address to find a person."<<endl;
		cout<<"If you would like to exit, please enter a period."<<endl;
		cin>>weird_lookup;
		if (weird_lookup=="."){
			break;
		}
		try{
		  //map.get (weird_lookup);
			cout << "key = " << weird_lookup<< " Person: " << map.get (weird_lookup) << endl;      
		}
		catch (int &dummy){
			cout << "key = " <<weird_lookup<< " not found" << endl;
		}
	}
	cout << "Exiting" << endl;

return 0;
}
