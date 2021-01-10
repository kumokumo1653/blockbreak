#include "field.h"
void initField(struct field* temp, double w, double h, GLuint images[], GLuint itemImage[]){
    temp -> width = w;
    temp -> height = h;
    temp -> wall[0] = line( vector(0, 0), vector(w, 0), 1.0); 
    temp -> wall[1] = line( vector(0, 0), vector(0, h), 1.0); 
    temp -> wall[2] = line( vector(w, h), vector(w, 0), 1.0); 
    temp -> wall[3] = line( vector(w, h), vector(0, h), 1.0); 

    //ブロック初期化
    int i,j;
    int width = 60;
    int height = 40;
    for(i = 0; i < 1;i++){
        struct vector p = vector(width / 2, h - height / 2 - i * height);
        for(j = 0; j < w / width;j++){
            temp -> blocks[j + i * (int)(w / width)] = block(1, 1,  1, p, width, height, 0, 1.0, (5 - i) * 100,images[i + 1]);
            p = add(p, vector(width,0));
        }
    }

    //アイテム初期化
    for(i = 0; i < ITEM; i++)
        temp->items[i] = item((enum type)i, EFFECT, itemImage[i]);
}
