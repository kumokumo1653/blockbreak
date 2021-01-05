#include "field.h"
void initField(struct field* temp, double w, double h){
    temp -> width = w;
    temp -> height = h;
    temp -> wall[0] = line(1, vector(100, 100), vector(300, 100), 1.0); 
    temp -> circle[0] = corner(1, vector(100,100), 50, M_PI, 2 * M_PI, 1.0);
}