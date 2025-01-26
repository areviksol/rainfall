#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(int arg) {
    char buffer[0x4c]; 
    fflush(stdout);

    gets(buffer);

    if ((arg & 0xb0000000) == 0xb0000000) {
        printf("Error: Invalid argument\n");
        exit(1);
    }

    puts(buffer);

    char *dup = strdup(buffer);

    free(dup);
}


int		main(void)
{
	p();
	return (0);
}