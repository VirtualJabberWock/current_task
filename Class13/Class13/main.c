#include <stdio.h>;
#include "../../aquaUtils/ArrayUtils.h"
#include "../../aquaUtils/DebugUtils.h"

typedef struct tagMove {
	/*N [00], S [01], E [10], W [11]*/
	char* dir;
	long long* distances;
	int moves_c;
} Move;

typedef struct tagPoint {
	__int64 x;
	__int64 y;
} Point;

int filterInput(string_t s, Move* out);

int main(int argc, const char** argv) {

	if (argc != 2) panic("Invalid args!");
	Move m;
	if (!filterInput(argv[1], &m)) panic("Bad input!");
	Point p = { .x = 0, .y = 0 };
	for (int i = 0; i < m.moves_c; i++) {
		int dir = m.dir[i];
		p.x +=  (m.distances[i] * !!(dir&2)) * (1-dir%2*2);
		p.y +=  (m.distances[i] *  !(dir&2)) * (1-dir%2*2);
	}
	printf("%d%c%d%c", abs(p.y), 'N'+5*(p.y < 0), abs(p.x), 'E'+18*(p.x < 0));
}

int filterInput(string_t s, Move* out) {
	int i = 0;
	int count = 0; int count_n = 0;
	out->dir = (char*)initArray(0, sizeof(char));
	char n_buffer[20];
	int n_ptr = 0;
	out->distances = (long long*)initArray(0, sizeof(long long));
	while (s[i] != '\0') {
		if ((s[i] >= '0') && (s[i] <= '9')) {
			n_buffer[n_ptr] = s[i]; n_ptr++;
			if (n_ptr > 19) return 0;
		}
		else {
			if (n_ptr != 0) {
				long long tmp;
				n_buffer[n_ptr] = '\0'; n_ptr = 0;
				sscanf_s(n_buffer, "%lld", &tmp);
				putTo64Array(&out->distances, &count_n, tmp);
			}
			if ((s[i] == 'N') || (s[i] == 'S')) {
				pushToCharArray(&out->dir, &count, (16 & s[i])>>4);
			}
			else if ((s[i] == 'W') || (s[i] == 'E')){
				pushToCharArray(&out->dir, &count, 2 + ((16 & s[i])>>4));
			}
			else return 0;
		}
		i++;
	}
	if (count != count_n) return 0;  
	out->moves_c = count;
	return 1;
}