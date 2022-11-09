#pragma once
#include "..\aquaUtils\pch.h"
#include "IPoint.h"

#define __PStackSelf__ struct tagPointStack* self

#define MAX_STACK_SIZE 512
#define DefaultPoint NullElement

typedef struct tagPointStack {

	PointV w_stack;
	int w_top;

	void (*push)(__PStackSelf__, PointP p);
	Point (*pop)(__PStackSelf__);
	Point (*peek)(__PStackSelf__); //of comedy
	void (*dispose)(__PStackSelf__);

	int (*isFull)(__PStackSelf__);
	int (*isEmpty)(__PStackSelf__);

} PointStack, *PointStackP;

Point NullElement;

void InitPointStack(PointStackP ps);

void _Default_PS_Push(__PStackSelf__, PointP p);
Point _Default_PS_Pop(__PStackSelf__);
Point _Default_PS_Peek(__PStackSelf__);
void _Default_PS_Dispose(__PStackSelf__);

int _Default_PS_isFull(__PStackSelf__);
int _Default_PS_isEmpty(__PStackSelf__);
