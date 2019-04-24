#include "lineseg.h"
#include "vec.h"
#include<iostream>

bool onLine(vec &p, vec &q, vec &r) {   //check whether p is on the line or not
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && 
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}

int direction(vec &a, vec &b, vec &c) {
   int val = (b.y - a.y)*(c.x - b.x) - (b.x - a.x) * (c.y - b.y);
   if (val == 0) {
      return 0;     //colinear
   }
   return (val > 0)? 1:2;
}


bool lineseg::intersects(lineseg &other) {
   //four direction for two lines and points of other line
   int dir1 = direction(this->a, this->b, other.a);
   int dir2 = direction(this->a, this->b, other.b);
   int dir3 = direction(other.a, other.b, this->a);
   int dir4 = direction(other.a, other.b, this->b);
   
   if(dir1 != dir2 && dir3 != dir4) {
      return true; //they are intersecting
   }	

   if(dir1==0 && onLine(this->a, other.a, this->b)) {//when p2 of line2 are on the line1
	   return true;
   }

   if(dir2==0 && onLine(this->a, other.b, this->b)) {//when p1 of line2 are on the line1
	   return true;
   }

   if(dir3==0 && onLine(other.a, this->a, other.b)) {//when p2 of line1 are on the line2
	   return true;
   }

   if(dir4==0 && onLine(other.a, this->b, other.b)) {//when p1 of line1 are on the line2
	   return true;
   }
   return false;
}
