#include <stdio.h>
#include <crypt.h>

void run() {
	char *crypted = crypt("des", "12tMnfw882VDQ");
	printf("Crypt output: %s\n", crypted);
}
