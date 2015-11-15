#include <stdio.h>

#define KRED "\x1B[31m"
#define KMAG "\x1B[35m"

int main(int argc, char** argv) {
	printf("\n%sred", KRED);
	//original KNRM
	printf(KMAG "magenta\n");
}
