// speed_test.cpp
#include <iostream>
#include <ctime>
// you may need more libraries

// list definitions
#include "alist.h"
//#include "ilist.h"
#include "iListLList.h"
#include "alistimpls.h"
//#include "arraylist.h"
//#include "plusonearraylist.h"
//#include "plustenarraylist.h"
//#include "doublingarraylist.h"
using namespace std;


double MeasureFrontInsertTime(IList<int> * list, int insertCount = 50000)
{
    double time = 0.0;
	clock_t start_insert=clock( );
    // time measurement code goes here

    for(int i = 0; i < insertCount; ++i) list->insert(0, i);
	
	clock_t end_insert= clock();
	time= double (end_insert-start_insert);
	//cout<<"Time is: "<<time<<endl;
    return time;
}

double MeasureBackInsertTime(IList<int> * list, int insertCount = 50000)
{
    double time = 0.0;
    // time measurement code goes here
	clock_t start_push_back = clock ();
	
    for(int i = 0; i < insertCount; ++i) list->insert(i, i);
    
	clock_t end_push_back = clock ( );
	time= double (end_push_back - start_push_back);
	//cout<<"Time for back insert is: "<<time<<endl;
	return time;
}

int main()
{
    double frontTime = 0.0, backTime = 0.0;
    IList<int> ** lists = new IList<int>*[8];

    // feel free to pass some argument to your constructor or just leave it to the default constructor
    lists[0] = new List <int>;          // front insert
    lists[1] = new List <int>;          // back  insert
    lists[2] = new PlusOneArrayList <int>;    // front insert
    lists[3] = new PlusOneArrayList <int>;    // back  insert
    lists[4] = new PlusTenArrayList <int>;    // front insert
    lists[5] = new PlusTenArrayList <int>;    // back  insert
    lists[6] = new DoublingArrayList <int>;   // front insert
    lists[7] = new DoublingArrayList <int>;   // back  insert

    for (int i = 0; i < 8; i += 2)
    {
        frontTime = MeasureFrontInsertTime(lists[i]);
        backTime  = MeasureBackInsertTime (lists[i + 1]);
		
		//PlusTenArrayList <int> plusTen;
		//plusTen.insert (0, 15);
		
		cout<<"lists of "<<i<<" has time: "<<frontTime<<" for front insert."<<endl;
		cout<<"lists of "<<i<<" has time: "<<backTime<<" for back insert."<<endl;
		
        // cout the duration in seconds

        // release: you can optionally measure delete (removing all items) duration
        delete lists[i];
        delete lists[i + 1];
    }
    delete [] lists;
    return 0;
}