#include "..\aquaUtils\pch.h"

#include "IPoint.h"
#include "Stack.h"
#include <string.h>

#define __ps currentPath

void handleCommand(string input_);
int handlePoint(string cmd, string input_);
void showHelp();
void doCalc();
int calcStack();
void goBack();

#define ERR_BAD_POINT_FORMAT "Bad point format. You can do it like (x,y) or (x, y) or {x, y} or x, y"
#define ERR_INT_OVERFLOW "Overflow: Point can storage coordinats only in int32"

PointStack currentPath;

void showHelp()
{
	printf("Usage:\n");
	printf("    'move (x, y)' - step forward to point and expand current path\n");
	printf("    'back' - step back to previous path tail\n");
	printf("    'calc' - calculate length of current path\n");
	printf("    'return' - do calc but free stack, and return to 0 point\n");
	printf("    'help' - for help\n");
	printf("    'exit' - exit\n");
	printf("    \n");
	printf("    Note: You can write point like tihs: (x,y) or (x, y) or {x, y} or x, y\n");
}


int main() {

	InitPointStack(&currentPath);

	printf("=-=-=-=-= Calc the path length =-=-=-=-=\n");
	showHelp();
	const char input_[2048];
	while(True){
		printf("\n> ");
		if (!gets(&input_)) {
			printf("Bad input!");
		}
		handleCommand(SUS_clearDublicateSpaces(input_));
	}
}

void handleCommand(string input_) {
	if (!strcmp(input_, "exit")) {
		currentPath.dispose(&currentPath);
		panic("Press any key to exit...\n");
		return;
	}
	if (!strcmp(input_, "back")) {
		goBack();
		return;
	}
	if (!strcmp(input_, "calc")) {
		doCalc();
		return;
	}
	if (!strcmp(input_, "return")) {
		calcStack();
		return;
	}
	
	if(handlePoint("move", input_) == 0) printf("Command don't exists.");
}

int handlePoint(string cmd, string input_)
{
	StringV sv;
	StringV s_point;
	InitStringV(&sv);
	InitStringV(&s_point);
	sv.ptr = SUS_split_match(input_, ' ', 2, &sv.size);

	if ((sv.size == 2) && (!strcmp(sv.ptr[0], cmd))) {
		s_point.ptr = SUS_split(sv.ptr[1], ',', &s_point.size);
		if (s_point.size != 2) {
			printf(ERR_BAD_POINT_FORMAT);
			printf("\nMETAINFO: %d, %s", s_point.size, sv.ptr[1]);
			return -1;
		}
		Point p;
		InitPoint(&p);
		int s = 0;
		s += SUS_parseInteger32_AnyWay(s_point.ptr[0], &p.x);
		s += SUS_parseInteger32_AnyWay(s_point.ptr[1], &p.y);
		if (s != 0) {
			printf(ERR_INT_OVERFLOW);
			return -1;
		}
		__ps.push(&__ps, &p);
		printf(
			"Added point {%d, %d} to current path[%d/%d]",
			p.x, p.y, __ps.w_top, MAX_STACK_SIZE
		);
		return 1;
	}
	return 0;
}

void goBack() {
	if (!__ps.isEmpty(&__ps)) {
		Point p = __ps.pop(&__ps);
		Point c = __ps.peek(&__ps);
		printf(
			"#Delete (%d, %d) and back to (%d, %d)",
			p.x, p.y, c.x, c.y
		);
	}
	else {
		printf("Empty history");
	}
}

int calcStack() {

	if (__ps.w_top == 0) return printf("Null path!");
	if (__ps.w_top == 1) return printf("Current path length = 0");
	double result = 0;
	Point peek, curr;

	while(!currentPath.isEmpty(&__ps)) {
		curr = currentPath.pop(&__ps);
		peek = currentPath.peek(&__ps);
		result += DefaultPoint.distanceTo(&curr, &peek);
	}

	printf("Current path length = %.5lf\nPath disposed [0/0]", result);
}

void doCalc()
{
	if (__ps.w_top < 2) {
		printf("Can't create a path with only single Point");
		return;
	}
	double result = 0;
	for (int i = 1; i < __ps.w_top; i++) {
		result += DefaultPoint.distanceTo(&__ps.w_stack[i], &__ps.w_stack[i - 1]);
	}

	printf("Current path length = %.5lf", result);
}