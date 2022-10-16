#include "pch.h";

#define ERR_NOT_A_NUMBER "Some number argument was not a number!"

typedef struct PointS {
	double x;
	double y;
} Point;

int strToDouble(string s, double* out);
int readPoints(string filename, Point* points);

int main(int argc, string* argv) {

	if (argc < 5) panic("Not enought args, should be only 4");
	if (argc > 5) panic("Too many arguments, should be only 4");
	
	double a,b,c;
	if (!strToDouble(argv[1], &a)) panic(ERR_NOT_A_NUMBER);
	if (!strToDouble(argv[2], &b)) panic(ERR_NOT_A_NUMBER);
	if (!strToDouble(argv[3], &c)) panic(ERR_NOT_A_NUMBER);

	string filename = argv[4];
	if (getStringLength(filename) > 100)
		panic("Filename too big (max is 100 chars).");

	Point* points;
	int readed = 0;
	int status = readPoints(filename, &points, &readed);
	if (status == 0) panic("File is empty!");
	if (status == -1) panic("File data not valid!");
	if (status == -2) panic("- File data not valid!");
	if (points == 0) panic("Memory error!");

	printf("%d points:\n", readed);
		
	for (int i = 0; i < readed; i++) {
		if ((a * points[i].x + b * points[i].y + c) == 0) {
			printf("%llf %llf: YES\n", (points[i]).x, (points[i]).y);
		}
		else {
			printf("%llf %llf: NO\n", (points[i]).x, (points[i]).y);
		}
	}
}

int strToDouble(string s, double* out) {
	if ((s[0] == '0') && (getStringLength(s) == 1)) {
		*out = 0.0;
		return 1;
	}
	double tmp = strtod(s, NULL);
	if (tmp == 0) return 0;
	*out = tmp;
	return 1;
}

int readPoints(string filename, Point** points, int* pcount)
{
	FILE* handle;
	string* lines = initBucket(0);
	openFileText_s(&handle, filename);
	int readed = 0;
	readAllLines_s(handle, &lines, &readed);
	closeFile(handle);
	if (readed == 0) return 0;
	(*points) = initList(readed, sizeof(Point));
	for (int i = 0; i < readed; i++) {
		int c = 0;
		int s = 0;
		
		string* coords = split(trim(lines[i]), ' ', &c);
		if (c != 2) break;
		s = strToDouble(coords[0], &((*points)[i].x));
		s = strToDouble(coords[1], &((*points)[i].y));
		if (s == 0) return -2;
	}
	freeBucket(lines, readed);
	*pcount = readed;
	return 1;
}
