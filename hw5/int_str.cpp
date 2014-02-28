#include <iostream>
#include <string>
#include "int_str.h"
using namespace std;

/*
istream& operator>> (istream &go, int_str &uni){
	go>>uni.variable>>uni.formula;'
	return go;
}
*/

int_str::int_str (int &other_variable){
	variable=other_variable;
	formula="NO";
}

int_str::int_str (string &other_formula){
	formula=other_formula;
	variable=-1;	
}

int_str::int_str (int &other_variable, string &other_formula){
	formula=other_formula;
	variable=other_variable;
}

int int_str:: variable_get ( ){
	return variable;
}

string int_str:: formula_get ( ){
	return formula;
}

bool int_str:: string_store ( ){
	bool string_store=false;
	if (variable==-1||formula!="NO"){
		string_store=true;
		return string_store;
	}
	return string_store;
}

bool int_str:: integer_store ( ){
	bool integer_store=false;
	if (formula=="NO"||variable!=-1){
		integer_store=true;
		return integer_store;
	}
	return integer_store;
}

bool int_str:: both_store ( ){
	bool both_store=false;
	if (formula!="NO"&&variable>-1){
		both_store=true;
		return both_store;
	}
	return both_store;
}

