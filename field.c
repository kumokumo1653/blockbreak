#include "field.h"
void initField(struct field* temp, double w, double h){
    temp -> width = w;
    temp -> height = h;
    temp -> wall[0] = line( vector(0, 0), vector(w, 0), 1.0); 
    temp -> wall[1] = line( vector(0, 0), vector(0, h), 1.0); 
    temp -> wall[2] = line( vector(w, 0), vector(w, h), 1.0); 
    temp -> wall[3] = line( vector(0, h), vector(w, h), 1.0); 

    temp -> blocks[0] = block(1, 1, 2, vector(200,200), 100, 10, 0, 1.0);
    temp -> blocks[1] = block(1, 0, 1, vector(200,300), 100, 10, 0, 1.0);
}