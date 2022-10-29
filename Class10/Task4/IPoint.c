#include "IPoint.h"
#include <math.h>

void InitPoint(PointP p)
{
	p->x = 0;
	p->y = 0;
	p->moveTo = _Default_Point_Move;
	p->shift = _Default_Point_Shift;
	p->distanceTo = _Default_Point_DistanceTo;
}

PointP _Default_Point_Move(__PointSelf__, PointP to) {
	self->x = to->x;
	self->y = to->y;
	return self;
}

PointP _Default_Point_Shift(__PointSelf__, PointP relative_shift) {
	self->x += relative_shift->x;
	self->y += relative_shift->y;
	return self;
}

double _Default_Point_DistanceTo(__PointSelf__, PointP to) {
	int dx = (to->x) - (int)(self->x);
	int dy = (to->y) - (int)(self->y);
	return pow(pow(dx, 2) + pow(dy, 2), 0.5);
}