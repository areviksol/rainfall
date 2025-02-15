#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128

void handle_auth(char *input) {
    if (strncmp(input, "auth ", 5) == 0) {
        _auth = (char *)malloc(4);
        strcpy(_auth, input + 5);
    }
}

void handle_reset(char *input) {
    if (strncmp(input, "reset", 5) == 0) {
        free(_auth);
    }
}

void handle_service(char *input) {
    if (strncmp(input, "service", 7) == 0) {
        _service = strdup(input + 8);
    }
}

void handle_login(char *input) {
    if (strncmp(input, "login", 5) == 0) {
        if (_auth && _auth[8] == 0) {
            fwrite("Password:\n", 1, 10, stdout);
        } else {
            system("/bin/sh");
        }
    }
}

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("%p, %p \n", _auth, _service);
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            return 0;
        }

        handle_auth(buffer);
        handle_reset(buffer);
        handle_service(buffer);
        handle_login(buffer);
    }

    return 0;
}

/* 

auth 
service aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
login

 */