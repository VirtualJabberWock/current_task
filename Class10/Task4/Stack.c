#include "Stack.h"

void InitPointStack(PointStackP ps)
{
	InitPoint(&NullElement);
	ps->w_stack = (Point*) calloc(MAX_STACK_SIZE, sizeof(Point));
	ps->w_top = 0;

	ps->push = _Default_PS_Push;
	ps->peek = _Default_PS_Peek;
	ps->pop = _Default_PS_Pop;
	ps->isEmpty = _Default_PS_isEmpty;
	ps->isFull = _Default_PS_isFull;
	ps->dispose = _Default_PS_Dispose;
}

void _Default_PS_Push(__PStackSelf__, PointP p) {
	if (!self->isFull(self)) {
		self->w_stack[self->w_top] = *p;
		self->w_top += 1;
	}
	else {
		panic("Error: PointStackOverflow!");
	}
}

Point _Default_PS_Pop(__PStackSelf__) {
	if (!self->isEmpty(self)) {
		int eax = self->w_top;
		self->w_top -= 1;
		return self->w_stack[eax-1];
	}
	else {
		panic("Error: EmptyStackException");
		return NullElement;
	}
}

Point _Default_PS_Peek(__PStackSelf__) {
	if (self->isEmpty(&self)) {
		panic("Error: EmptyStackException");
		return NullElement;
	}
	return self->w_stack[self->w_top-1];
}

void _Default_PS_Dispose(__PStackSelf__) {
	free(self->w_stack);
}

int _Default_PS_isFull(__PStackSelf__) {
	return (self->w_top >= MAX_STACK_SIZE);
}

int _Default_PS_isEmpty(__PStackSelf__) {
	return (self->w_top == 0);
}