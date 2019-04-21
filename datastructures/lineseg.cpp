#include "lineseg.h"
#include "vec.h"
#include<iostream>

bool onLine(lineseg *l1, vec *p) {   //check whether p is on the line or not
   if(p->x <= std::max(l1->a->x, l1->b->x) && p->x <= std::min(l1->a->x, l1->b->x) &&
      (p->y <= std::max(l1->a->y, l1->b->y) && p->y <= std::min(l1->a->y, l1->b->y)))
      return true;
   
   return false;
}

int direction(vec *a, vec *b, vec *c) {
   int val = (b->y-a->y)*(c->x-b->x)-(b->x-a->x)*(c->y-b->y);
   if (val == 0)
      return 0;     //colinear
   else if(val < 0)
      return 2;    //anti-clockwise direction
      return 1;    //clockwise direction
}

bool lineseg::intersects(lineseg *other) {
   //four direction for two lines and points of other line
   int dir1 = direction(this->a, this->b, other->a);
   int dir2 = direction(this->a, this->b, other->b);
   int dir3 = direction(other->a, other->b, this->a);
   int dir4 = direction(other->a, other->b, this->b);
   
   if(dir1 != dir2 && dir3 != dir4)
      return true; //they are intersecting

   if(dir1==0 && onLine(this, other->a)) //when p2 of line2 are on the line1
      return true;

   if(dir2==0 && onLine(this, other->b)) //when p1 of line2 are on the line1
      return true;

   if(dir3==0 && onLine(other, this->a)) //when p2 of line1 are on the line2
      return true;

   if(dir4==0 && onLine(other, this->b)) //when p1 of line1 are on the line2
      return true;
         
   return false;
}
