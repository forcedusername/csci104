#include <iostream>
#include <fstream>
//#include <vector>

using namespace std;

void painful_maps (int color_num, char** letters, int** colors, int rows, int columns);
bool neighbor_valid (char country, int color_num, char** letters, int** colors, int rows, int columns);
void coloring (char country, int color_num, char** letters, int** colors, int rows, int columns);

int main (int argc, char* argv [ ]){
	ifstream input (argv [1]);
	
	int country_map=0;
	input>>country_map;
	int map_rows=0;
	input>>map_rows;
	int map_columns=0;
	input>>map_columns;
	
	 //this isnt an actual array, each row will have a pointer to an array.
	 //that array at each row will be the columns and then you can input things
	 //one array for chars from file, other array for colors 
	char** random= new char* [map_rows];
	int** color_key= new int* [map_rows];
//	char country_start;
	int color_start=1;
//	int row_index=0;
//	int column_index=0;
	
	//how do i make a map from the file stuff?
	for (int i=0; i<map_rows;i++){
		random [i]= new char [map_columns]; 
		color_key [i]= new int [map_columns];
		for (int j=0; j<map_columns;j++){
			input>>random [i][j]; //im not sure if this works
			color_key [i][j]=0; //might as well just initialize everything to zero to avoid weirdness
		}
	}
	painful_maps (color_start, random, color_key, map_rows, map_columns);
	return 0;
}

//pass in index instead of char and increment column then row
//stop it when you reach last column, then go to next row and stop once you reach last square
void painful_maps (int color_num, char** letters, int** colors, int rows, int columns){
  char country;
	for (int i=0; i<rows; i++){
		for (int j=0; j<columns;j++){
      if (colors[i][j] != 0)
      {
        // Already visited.
        continue;
      }
      country = letters [i][j];
      bool legal=neighbor_valid (country, color_num, letters, colors, rows, columns);
      if (legal==false)
      {
        color_num++;
        if (color_num > 4)
          color_num = 1;
        painful_maps (color_num, letters, colors, rows, columns);
        return;
      }
      else
      {
		coloring (country, color_num, letters, colors, rows, columns);        
      }
		}
  }    
} 

void coloring (char country, int color_num, char** letters, int** colors, int rows, int columns){
  cout<< country << ":" << color_num << endl; 
	for (int i=0;i<rows;i++){
		for (int j=0;j<columns;j++){
			if (letters [i][j]==country){
				colors [i][j]=color_num;
			}
		}
	}
}

bool neighbor_valid (char country, int color_num, char** letters, int** colors, int rows, int columns){
	bool valid=true;
	//cout<<"entering neighbor valid."<<endl;
	for (int i=0;i<rows;i++){
		for (int j=0;j<columns;j++){
			//cout<<"entering for loop"<<endl;
			if (letters [i][j]==country){
				if (colors [i][j]!=0){ //come back to this one
				//cout<<"If not 0"<<endl;
					valid=false;
					return valid;
				}
  
				if (i-1>=0){
					//cout<<"i-1"<<endl;
					if (letters [i-1][j]!=country){
						if (colors [i-1][j]==color_num){
							valid=false;
							return valid;
						}
					}
				}
				if (j-1>=0){
					//cout<<"j-1"<<endl;
					if (letters [i][j-1]!=country){
						if (colors [i][j-1]==color_num){
							valid=false;
							return valid;
						}
					}
				}
				if (i+1<rows){
					//cout<<"i+1"<<endl;
					if (letters [i+1][j]!=country){
						if (colors [i+1][j]==color_num){
							valid=false;
							return valid;
						}
					}
				}
				if (j+1<columns){
					//cout<<"j+1"<<endl;
					if (letters [i][j+1]!=country){
						if (colors [i][j+1]==color_num){
							valid=false;
							return valid;
						}
					}
				}
			//j-1>=0||i+1<rows||j+1<columns){
			}// if country
		}//for j
	}//for i
	//cout<<"returning from legal check"<<endl;
	return valid;
}
