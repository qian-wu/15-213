#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

struct Node{
	int tag;
	int low;
	int high;
	struct Node *next;
};

struct Set{
	int size;
	struct Node *entries;
};

int hit, miss, evic;

// init cache, if error retur -1;
int initCache(struct Set sets[], int size, int entries) {
	for (int i = 0; i < size; i++) {
		sets[i].size = 0;
		sets[i].entries = NULL;
	}
	return 0;
}

int addHead(struct Set *set, int in_tag, int block_i) {
	// printf("add node at head now set size is %d get tag %d\n", set->size, in_tag);
	struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
	if (!new_node) {
		printf("malloc new node error");
		exit(-1);
	}
	new_node->tag = in_tag;
	new_node->low = 0;
	new_node->high = 15;
	if (set->entries != NULL) {
		new_node->next = set->entries->next;
		set->entries->next = new_node;
	} else {
		new_node->next = NULL;
		set->entries = new_node;
	}
	set->size++;
	// if (set->entries) 
	// 	printf("after add node get tag %d set tag %d set size %d\n", in_tag, set->entries, set->size);

	return 1;
}

int removelast(struct Set *set) {
	if (set->entries->next != NULL) {
		while (set->entries->next->next) ;
		set->entries->next = NULL;
	} else {
		set->entries = NULL;
	}
	return 1;
}

int getNode(struct Node *head, int tag, int block_i) {
	// printf("search on %d", head);
	while (head) {
		// printf("search on tag %d", head->tag);
		if (head->tag == tag) {
			printf("hit ");
			return 1;
		}
		head = (struct Node *)head->next;
	}
	return 0;
}

// search cache, 
// if hit return 1, printf hit;
// else print miss, add new node , evic or not; 
// error return -1;
int searchCache(struct Set sets[], int addr, int block, int s, int e, int b, char oper) {
	// get set index
	int mask_s = (0x1 << (s + b)) - 1;
	int set_i = (mask_s & addr )>> b;
	// get block 
	int mask_b = (0x1 << b) - 1;
	int block_i = mask_b & addr;
	// get tag
	int mask_t = 0xffffffff ^ mask_s;
	int tag = (mask_t & addr) >> (s + b);
	printf("\ttag %x set %x block %x \n", tag, set_i, block_i);

	// get target set
	struct Set *tag_set = &sets[set_i];
	struct Node *head = tag_set->entries;
	// if target set is empty, print Miss, add new node 
	if (!head) {
		printf("miss ");
	} else {
		if (getNode(head, tag, block_i)) {
			return 1;
		} else if (tag_set->size == e){ //if size == 5, printf "eviction"
			printf("miss ");
			printf("eviction ");
			removelast(tag_set);
			tag_set->size--;
		} else {
			printf("miss size is %d e = %d", tag_set->size, e);
		}
	}

	addHead(tag_set, tag, block_i);
	// printf("add node on set %d tag %d set to %d now size %d \n", set_i, tag, tag_set->entries->tag, tag_set->size);
	
	
	// when miss add new node at head
	if (oper == 'M') {
		getNode(tag_set->entries, tag, block_i);
	}

	return 1;
}

// parse line input to oper & addr
int parseLine(char *line, struct Set sets[], int s, int e, int b) {
	// get oper
	
	int tmp;
	char oper = line[1];
	// get address
	char addrc[20];
	int length = strlen(line), i;
	for (i = 3; i < length; i++) {
		if(line[i] != ',') {
			addrc[i - 3] = line[i];
		}else {
			break;
		}
	}
	int addr = strtol(addrc, NULL, 16);
	int block = line[i + 1] - 48;

	printf("\toper %c addr 0x%x block %d\n", oper, addr, block);

	// search cache, call searchCache()
	searchCache(sets, addr, block, s, e, b, oper);

	return -1;
}

int main(int argc, char *argv[]) {
	int opt;
	int h, v, s, b, e;
	char *t;

	
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

	int S = 1 << s;
	int B = 1 << b;

	struct Set *sets = (struct Set *) malloc(sizeof(struct Set) * S);
	if (!sets) {
    	printf("malloc sets error\n");
        exit(-1);
    }

    FILE  *fp = fopen("./traces/yi.trace", "r");

    // initCache(sets, S, e);
    char buff[255];
    int i = 0;
    while (!feof(fp)) {
    	fgets(buff, 255, fp);
    	printf("\n  %s", buff);
    	parseLine(buff, sets, s, e, b);
    	// break;
    }

    // char *ch = " L 110,1\n";
    // parseLine(ch, sets, s, e, b);
    fclose(fp);
	return 0;
}























