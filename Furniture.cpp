#include <iostream>
#include <cstdlib>

#include "Furniture.h"
using namespace std;



void Furniture::set_name(string name){
this->name = name;
}
 string Furniture::get_name(){
 return this->name;
 }

void Furniture::set_size_2D(float size_2D){
this->size_2D = size_2D;
}
float Furniture::get_size_2D(){
return this->size_2D;
}




