/*
 * File:   main.cpp
 * Author: wissem
 *
 * Created on November 10, 2015, 11:50 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream> // reading from a file
#include <vector>
#include <typeinfo>

#include "Furniture.h"
#define quote(x) #x
/**
Structure called space contain a name of a space,
his volume and whether it's free or not **/
struct space {
    char name;
    int center_x;
    int center_y;
    int adjust;
    float volume = 0;
    bool free = true;
    };

/* Function to Fill Quarters by numbers, each number represent an area; */
void Fill_Rec(char (&a)[10][10],int &inc,int center_x,int center_y,int adjust,std::vector<space>& liste,bool &check);
/* Funtion to Check whether an Area should subdivised to small areas or not */
bool Check_Part(int (&Our_Space)[10][10],int center_x,int center_y,int adjust);


using namespace std;
int main(int argc, char** argv) {


Furniture fff;

/**
 Our input and output files
 **/
   ifstream fin("input.txt", std::ios::in);
   ofstream fout("output.txt", std::ios::out);
   int rows_number,lines_number;


   // read number of rows and lines
   fin>>rows_number;
   lines_number= rows_number;
   cout<<rows_number<<endl;
   // create Matrix called ourSpace
   int Our_Space[10][10]={0};
   int a;
   int i=0; int j=0;



   /**  Fill the matrix from the input file **/

   while(fin) {

           fin>>a;
            j++;
           if (j%rows_number == 0 ){

               fout<<a<<endl;
               Our_Space[i][j-1]= a;i++;j=0;
           }
           else if (i < lines_number){

               fout<<a<<" ";
               Our_Space[i][j-1]= a;
           }

   };

cout<< Our_Space[7][0] << endl;
   // Show the matrix on console
   for(i=0;i<lines_number;i++) {

       for (j=0;j<rows_number;j++){

          cout<< Our_Space[i][j]<<" ";
     }
     cout<<endl;
  };
cout<<endl;

/* It's OK */

  // Generate the new Matrix
 char New_Space[10][10];
 vector<space> liste;
 liste.push_back(space());
 liste[0].name = 'A';
 liste[0].center_x = rows_number/2;
 liste[0].center_y = lines_number/2;
 liste[0].adjust = lines_number/2;
 liste[0].volume = lines_number * rows_number;

  int letter = 65;// We consider the whole space as available



  int center_x,center_y,adjust;



int step = 1;
bool check = true;
while (step < 8){

center_x = liste[step-1].center_x;
center_y = liste[step-1].center_y ;
adjust = liste[step-1].adjust;


// Check whether partition or not;
     bool B = Check_Part(Our_Space,center_x,center_y,adjust);

       if (B == true) {

          cout<< "Partition"<<endl;

           if (adjust == 1 && check ){ adjust++; check = false; }
      cout<< liste[step-1].name << endl;
          Fill_Rec(New_Space,letter, center_x, center_y,adjust/2,liste,check);

        }
        else {


          cout<< "Dont Partion"<<endl;

         }

  step++;
}

/* This operation calculate the volume */
int mm,nn;
    for (i=0;i<lines_number;i++){
        for (j=0;j<rows_number;j++){
            mm = New_Space[i][j];
            nn = mm - 65;
            liste[nn].volume ++;

        }

}

/* This operation show the content of each liste's block*/
while (!liste.empty())
  {
     cout << liste.back().name << "("<<liste.back().center_x<< ","<< liste.back().center_y<<") adjust = "<<liste.back().adjust<<" Volume = "<<liste.back().volume <<endl;

    liste.pop_back();
  }

 //////////////////////////////////////////



// Show the new matrix on console
   for(i=0;i<lines_number;i++) {
       for (j=0;j<rows_number;j++){

          cout<< New_Space[i][j]<<" ";
     }
     cout<<endl;
  };
cout<<endl;

string name,inp, type;
float area=NULL;
vector<Furniture> Furniture_liste;

do {

cout<< type << endl;
name = type;
Furniture type;
if (area!=NULL){
cout<< area << endl;
}

type.set_name(name);
cout<< type.get_name() << endl;


Furniture_liste.push_back(type);
}
while (cin >> type && cin >> area && type != "end");

for(i = 1;i<Furniture_liste.size();i++){
cout<< " testinng : "<< Furniture_liste[i].get_name() << endl;
}



  fin.close();

  return 0;
}

/**

Think about reducing adjust from center_x and center_y instead of dividing :D


**/




void Fill_Rec(char (&a)[10][10],int &inc,int center_x,int center_y,int adjust,std::vector<space>& liste,bool &check) {
int i,j=0;
int limits = 2*adjust;;
int start_point_x,end_point_x,start_point_y,end_point_y;


 if (adjust == 1 && check==false ){
  start_point_x = center_x - adjust;
  end_point_x = center_x + adjust;
  start_point_y = center_y - adjust;
  end_point_y = center_y + adjust;
  limits = 1;
   }
    else {
   start_point_x = center_x - limits;
   end_point_x = center_x + limits;
   start_point_y = center_y - limits;
   end_point_y = center_y + limits;
}



 //First Quarter
 inc++;
 char c = inc;
  liste.push_back(space());
  liste[inc-65].name = c;
  liste[inc-65].center_x = center_x - adjust;
  liste[inc-65].center_y = center_y - adjust;
  liste[inc-65].adjust = adjust;

   for (i = start_point_y; i<end_point_y-limits ;i++){
        for( j = start_point_x; j<end_point_x-limits; j++){

           a[i][j]= c;
        }
   }
 //Second Quarter
 inc++;
 c = inc;
  liste.push_back(space());
  liste[inc-65].name = c;
  liste[inc-65].center_x = center_x + adjust;
  liste[inc-65].center_y = center_y - adjust;
  liste[inc-65].adjust = adjust;

   for (i = start_point_y; i<end_point_y-limits ;i++){
        for( j = start_point_x+limits; j<end_point_x; j++){

           a[i][j]= c;
        }
   }
   //Third Quarter
 inc++;
 c = inc;
  liste.push_back(space());
  liste[inc-65].name = c;
  liste[inc-65].center_x = center_x - adjust;
  liste[inc-65].center_y = center_y + adjust;
  liste[inc-65].adjust = adjust;

   for (i = start_point_y+limits; i<end_point_y ;i++){
        for( j = start_point_x; j<end_point_x-limits; j++){

           a[i][j]= c;
        }
   }
 //Fourth Quarter
 inc++;
 c = inc;
  liste.push_back(space());
  liste[inc-65].name = c;
  liste[inc-65].center_x = center_x + adjust;
  liste[inc-65].center_y = center_y + adjust;
  liste[inc-65].adjust = adjust;

   for (i = start_point_y+limits; i<end_point_y ;i++){
        for( j = start_point_x+limits; j<end_point_x; j++){

           a[i][j]= c;
        }
   }
}

bool Check_Part(int (&Our_Space)[10][10],int center_x,int center_y,int adjust){

int i,j;
int m=0;
int n=0;
int start_point_x = center_x - adjust;
int end_point_x = center_x + adjust;
int start_point_y = center_y - adjust;
int end_point_y = center_y + adjust;

 for ( i = start_point_y; i< end_point_y-1 ;i++){
     m++;
    for ( j = start_point_x; j< end_point_x-1;j++){
         n++;
          if (Our_Space[i][j] != Our_Space[i][j+1])
           goto getout;
    }

}
getout: cout<< i<< " :  "<<j <<endl;

if (adjust == 1) { return ( m != n) || (Our_Space[i][j] != Our_Space[i][j+1]);}
else
{
return (i != j) || (Our_Space[end_point_y-1][end_point_x-2]!=Our_Space[end_point_y-1][end_point_x-1]) ;
}
}

