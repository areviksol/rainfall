#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[80];

void m(void)
{
    printf("%s - %d\n", c, time(0));
    return;
}

int main(int argc, char **argv)
{
    char *size;
    FILE *stream;

    char *a1 = malloc(8);
    *a1 = 1;
    void **gl2 = malloc(8);
    a1[1] = gl2;
    char *a3 = malloc(8);
    *a3 = 2;
    void **gl2 = malloc(8);
    a3[1] = gl2;

    strcpy(a1[1], argv[1]);
    strcpy(a3[1], argv[2]);

    gl2 = fopen("/home/user/level8/.pass", "r");
    fgets(c, 68, gl2);
    puts("~~");
    return 0;
}
