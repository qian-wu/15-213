#include <stdio.h>

int vlevel;
unsigned int cookie = 1;

/* Compare string to hex represention of unsigned value */
int hexmatch(unsigned val, char *sval)
{
 char cbuf[110];
 /* Make position of check string unpredictable */
 char *s = cbuf + random() % 100;
 printf("%x \n", s);
 sprintf(s, "%.8x", val);
 printf("%.8x \n", *s);
 return strncmp(sval, s, 9) == 0;
}

void touch3(char *sval)
{
 vlevel = 3; /* Part of validation protocol */
 if (hexmatch(cookie, sval)) {
 printf("Touch3!: You called touch3(\"%s\")\n", sval);
 } else {
 printf("Misfire: You called touch3(\"%s\")\n", sval);
 }
}

int main() {
	char *sval = "1";
	touch3(sval);
}