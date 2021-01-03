#include "corner.h"
struct corner corner(int exist, int out, struct vector center, double r, double startAngle, double endAngle, double e){
    struct corner temp = {exist, out, center, r, startAngle, endAngle, e};
    return temp;
}