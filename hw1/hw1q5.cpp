#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

void pain_recurse (int desire_length, string randomstring, int counter, char* place, int base);

int main (int argc, char* argv[ ]){
  if (argc<3){
    cout<<"Enter command line arguments"<<endl;
  }
  int desire_length= atoi (argv [2]);
  
  string randomstring= argv [1];
  int base= randomstring.length ( );
 
  int counter=desire_length;
  char* place= new char [desire_length+1];
  
  pain_recurse (desire_length, randomstring, counter, place, base);
  
  return 0;
}

void pain_recurse (int desire_length, string randomstring, int counter, char* place, int base){
  //cout<<"entering function"<<endl;
  
  if (counter==1){
    for (int i=0; i<base;i++){
      place [counter]=randomstring [i];
      for (int j=1; j<desire_length+1; j++){
        cout<<place [j];
      }
      cout<<'\n';
    }
    return;
  }
  
  if (counter>1){
    for (int i=0; i<base; i++){
      place [counter]=randomstring [i];
      pain_recurse (desire_length, randomstring, counter-1, place, base);
    }
  
  }

}
