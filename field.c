#include "field.h"
void initField(struct field* temp, double w, double h){
    temp -> width = w;
    temp -> height = h;
    temp -> wall[0] = line(1, vector(200, 100), vector(300, 100), 1.0); 
}