#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "stack_template.h"
#include "int_str.h"
#include "map.h"

using namespace std;

Stack <int_str>* stack_up (string &expression);
void process_expression(string &expression, Map<int,char> &truth_table);
bool reduceExpression(Stack<int_str> &expressStack, Map<int,char> &truth_table);
void finalizeExpression(Stack<int_str> &expressStack, Map<int,char> &truth_table);
bool popOperator(Stack<int_str> &expressStack, Map<int,char> &truth_table, string &opr);
bool popOperand(Stack<int_str> &expressStack, Map<int,char> &truth_table, char &truth_value);

int main (int argc, char* argv[ ]){

	if (argc<3){
		cout<<"Insufficient Arguments, run again. [<cmd> <expression> <truth>]"<<endl;
		return 0;
	}
	
	//have an array list of strings to store the stuff from file formula 
	//have a separate array of strings to store your variable assign
	//maybe the classes solution is better....
	
	string variable_holder;
	string formula_holder;
	
	vector <string> expression_vector;
	
	Map <int, char> truth_table;
	
	ifstream file_formula (argv [1]);
	ifstream variable_assign (argv [2]);
	
	while (getline (file_formula, formula_holder)){
		expression_vector.push_back (formula_holder);
		formula_holder.clear();
	}
	cout<<"Formula holder success. num expressions = "<< expression_vector.size() << endl;
	int variable;
	char truth;

	while (getline (variable_assign, variable_holder)){

    stringstream sstream(variable_holder);
    sstream >> variable;
    sstream >> truth;

		truth_table.add (variable, truth);
		variable_holder.clear ();
	}
	//cout<<"Truth Table success...size ="<< truth_table.size() << endl;
	
	file_formula.close ( );
	variable_assign.close ( );
	
	//vector <Stack <int_str>* > formula_store;
	unsigned int x=0;
	while (x<expression_vector.size()){
    process_expression(expression_vector[x], truth_table);
		//formula_store.push_back (stack_up(expression_vector[x]));
		x++;
	}
	cout<<"Successful stack vector built."<<endl;

return 0;
}

void process_expression(string &expression, Map<int,char> &truth_table)
{
	unsigned int x=0;
	cout<<"Entering  [" << expression << "]" <<endl;
	Stack<int_str> expressStack;
	char elem;
	bool digitOn      = false;
	int inxDigitBegin = 0;
	int intvalue;
	bool retval       = true;
	
	while (x<expression.size()){
		elem = expression[x];
		if (digitOn == true)
		{
			if (isdigit(elem)){
				x++;
				continue;
			}
			string digitString = expression.substr(inxDigitBegin,(x-inxDigitBegin));
			intvalue = atoi(digitString.c_str());
			int_str sample(intvalue);
			digitOn = false;
			expressStack.push(sample);
		}
		else{
			if (isdigit(elem)){
				digitOn = true;
				inxDigitBegin = x;
				x++;
				continue;
			}
		}
    // this is in case of non digits i.e '(' , ')', '&', '|', '~'
		if (elem == ' '){
			x++;
			continue;
		}
		if (elem == '(' || elem == '&' || elem == '|' || elem == '~'){
			string str = expression.substr(x,1);
			int_str sample2(str);
			expressStack.push(sample2);
		}
		if (elem == ')'){
			retval = reduceExpression(expressStack, truth_table);
			if (retval == false)
				break;
		}
		x++;
	}//while
  // now process the stack and finalize expression.
	if (retval == true){
		finalizeExpression(expressStack, truth_table);
	}
	cout<<"Successful processed [" << expression << "]" <<endl;
} //END process_expression
	
void  finalizeExpression(Stack<int_str> &expressStack, Map<int,char> &truth_table)
{
  char truth_value1;
  string opr;
  if (popOperand(expressStack, truth_table, truth_value1) == false)
     return;
     
  while (1)
  {
    if (expressStack.size() == 0)
    {
      cout << "Truth value of expression " << truth_value1 << endl;
      break;
    }
    if (popOperator(expressStack, truth_table, opr) == false)
    {
      break;
    }
    if (opr != "~")
    {
      cout<<"Malformed expression."<<endl;
      break;
    }
    if (truth_value1== 'T')
      truth_value1 = 'F';
    else
      truth_value1 = 'T';
  }
} //END finalizeExpression
bool reduceExpression(Stack<int_str> &expressStack, Map<int,char> &truth_table)
{
  char truth_value1;
  char truth_value2;
  string paran;
  while (1)
  {
    string opr;
    if (popOperand(expressStack, truth_table, truth_value1) == false)
    {
      return false;
    }
    //(2&(3|4)) --->  '(' '2' '&' '(' '3' '|' '4' ')' ---> '(' '2' '&' '(' '3' '|'
    // '(' '2' '&' 'T')
    while (1)
    {
      if (popOperator(expressStack, truth_table, opr) == false)
      {
        return false;
      }
      if (opr != "~")
      {
        break;
      }
      if (truth_value1== 'T')
        truth_value1 = 'F';
      else
        truth_value1 = 'T';
    }
    if (popOperand(expressStack, truth_table, truth_value2) == false)
    {
      return false;
    }
    while (1)
    {
      if (popOperator(expressStack, truth_table, paran) == false)
      {
        return false;
      }
      if (paran != "~")
      {
        break;
      }
      if (truth_value2== 'T')
        truth_value2 = 'F';
      else
        truth_value2 = 'T';
    }
    if (paran != "(")
    {
      int_str oprval(paran);
      expressStack.push(oprval);
    }
    string strTruth("F");
    
    if (opr == "&")
    {
      if (truth_value1 != 'F' && truth_value2 != 'F')
        strTruth = "T";
    }
    else if (opr=="|")
    {
      if (truth_value1=='T' || truth_value2=='T'){
        strTruth="T";
      } 
    }
    int_str expressVal(strTruth);
    expressStack.push(expressVal);
    // paran OR an operator.
    if (paran == "(")
    {
      break;
    }
  }
  return true;
} //END reduceExpression
/*
  ~~(2 & 7& ( ~5000000000 |~0))
  ~ ~ ( 2 & 7 & ( ~ 5000 | ~ 0 ) )
  ~ ~ ( 2 & 7 & 'T' )
  ~ ~ ( 2 & 7 & 'T' 
  ~ ~ ( 2 & 'F'
  ~ ~ ( 2 & 'F'
  ~ ~ 'T'
  ~~~~~20000
  ~2000
*/
bool popOperand(Stack<int_str> &expressStack, Map<int,char> &truth_table, char &truth_value)
{
	int_str top= expressStack.top( );
	expressStack.pop();
	if (top.string_store ()==true){
		string str = top.formula_get();
		if (str == "T"){
			truth_value = 'T';
			return true;
		}
		else if (str == "F"){
			truth_value = 'F';
			return true;
		}
		cout<<"Malformed expression."<<endl;
		return false;
	}  
	int key = top.variable_get();
	try {
		truth_value=truth_table.get (key);
    } 
	catch (int e){
		cout<<"Malformed expression.(variable not found)"<<endl;
		return false;
	} 
	return true;
} // end popOperand
bool popOperator(Stack<int_str> &expressStack, Map<int,char> &truth_table, string &opr)
{
  int_str top = expressStack.top( );
  if (top.integer_store() ==true){
    cout<<"Malformed expression."<<endl;
    return false;
  }  
  expressStack.pop();
  opr = top.formula_get();
  return true;  
}// end popOperator

/*
Stack <int_str>* stack_up (string &expression){
	Stack <int_str>* good_stack= new Stack <int_str>;
	
	unsigned int x=0;
	while (x<expression.size()){
		char first_elem= expression [x];
		//you can only have the ascii values of (, ), {, }, |, & , ' ' so anything other than this
		//is a number
		int ascii;
		ascii=first_elem;
		if (ascii==' '){
			expression.erase (expression[x]);
			//this means you have a space, hopefully the compiler wont yell 
		}
		if (ascii!=38||ascii!=40||ascii!=41||ascii!=91||ascii!=93||ascii!=123||ascii!=124||ascii!=125||ascii!=126){
			//this means you dont have a paranthesis/bracket/or/and operator
			int number=first_elem-'0';
			int_str getter (number);
			good_stack->push_back (getter);
		}
		x++;
	}
	cout<<"Successful stack built"<<endl;
  return good_stack;
}
*/