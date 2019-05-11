#include <stdio.h>

int main() {
	char *s = "59b997fa";
	for (int i = 0; i < 8; i++) {
		printf("%x ", *s);
		s = s + 1;
	}
}