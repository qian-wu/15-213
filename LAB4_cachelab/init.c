#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int opt;
	int h, v, s, b, e;
	char *t;

	while((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
		switch(opt) {
			case 'h':
				h = 1;
				printf("has arg h\n");
				break;
			case 'v':
				v = 1;
				printf("has arg v\n");
				break;
			case 's':
				s = (int)*optarg - '0';
				printf("s: %d\n", s);
				break;
			case 'E':
				e = (int)*optarg - '0';
				printf("E: %d\n", e);
				break;
			case 'b':
				b = (int)*optarg - '0';
				printf("b: %d\n", b);
				break;
			case 't':
				t = optarg;
				printf("t: %s\n", t);
				break;
			case '?':  
                printf("unknown option: %c\n", optopt); 
                break; 

		}
	}

	return 0;
}