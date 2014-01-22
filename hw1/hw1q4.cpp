#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int main (int argc, char* argv [ ]){
  ifstream input (argv [1]);
  int lines=0;
  input>>lines;
  
  int* num_words= new int [lines];
  bool word= false; 
  for (int i=0; i<lines; i++){
    int words_line=0;
    num_words [i]= words_line;
    char words [81];
    
    input.getline (words, 80); 
    for (int j=0; j<80&&words[j]!='\0'; j++){
      if (words [j]==' '||words[j]=='\t'){
        word= false; 
        continue;  
      }
      if (word==false){
        word= true;
        words_line++;
      }
    
    }
    num_words [i]= words_line;
  }
  
  for (int x=lines-1; x>=0; x--){
    cout<<num_words [x]<<endl;
  }

  input.close ( );
return 0;

}
