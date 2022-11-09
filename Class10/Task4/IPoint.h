#pragma once
#include "..\aquaUtils\pch.h"

#define __PointSelf__ struct tagPoint* self
#define __PointPtr__ struct tagPoint*


typedef struct tagPoint {

	int x;
	int y;
	__PointPtr__(*moveTo) (__PointSelf__, __PointPtr__ to);
	__PointPtr__(*shift) (__PointSelf__, __PointPtr__ relative_shift);
	double (*distanceTo) (__PointSelf__, __PointPtr__ to);
		
} Point, *PointP, *PointV;

void InitPoint(PointP p);

PointP _Default_Point_Move(__PointSelf__, PointP to);
PointP _Default_Point_Shift(__PointSelf__, PointP relative_shift);
double _Default_Point_DistanceTo(__PointSelf__, PointP to);