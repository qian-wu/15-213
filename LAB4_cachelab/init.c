#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	int low;
	int high;
	struct Node *next;
} Node;

typedef struct{
	int size;
	Node *entry;
} Set;

int hit, miss, evic;

// init cache, if error retur -1;
int initCache(Set sets[], int size, int entries) {
	for (int i = 0; i < size; i++) {
		Set *tmp = &sets[i];
		tmp->size = 0;
		tmp->entry = (Node *) malloc(sizeof(Node) * entries);
		if (!tmp->entry) {
    		printf("malloc entry on set %d error\n", i);
        	exit(-1);
		}
	}
	return 0;
}

// search cache, 
// if hit return 1, printf hit;
// else print miss, add new node , evic or not; 
// error return -1;
int searchCache(Set sets[], int addr) {
	return -1;
}

// parse line input to oper & addr
int parseLine(char *line, Set sets[], int size) {

	// parse oper, addr

	// search cache, call searchCache()

	return -1;
}

int main(int argc, char *argv[]) {
	int opt;
	int h, v, s, b, e, S, B;
	char *t;
	FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

	// get parameters, parse into variables
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

	S = pow(2, s);
	B = pow(2, b);

	Set *sets = (Set *) malloc(sizeof(Set) * S);
	if (!sets) {
    	printf("malloc sets error\n");
        exit(-1);
    }

    initCache(sets, S, e);
    // Set *a = &sets[0];
    // a->entry[0].low = 1;
    // a->entry[1].low = 2;

    // printf("%d %d\n", sets[0].size, a->entry->low);

    //open file on parameter -t
	fp = fopen("./traces/yi.trace", "r");
    if (fp == NULL) {
    	printf("Can not open file. %s\n", t);
        exit(-1);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
        parseLine(line, sets, S);
    }


    fclose(fp);
	return 0;
}























