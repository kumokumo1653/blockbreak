#include "flipper.h"
void initFlipper(struct flipper *temp, struct vector start, struct vector end, double s, double e){
    temp -> end = end;
    temp -> start = start;
    temp -> sr = s;
    temp -> er = e;
    temp -> omega = 0;
}