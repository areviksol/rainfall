#include <iostream>
#include <cstring>
#include <cstdlib>

class N {
public:
    int value;
    char *str;

    N(int val) : value(val) {}

    int operator+(N& other) {
        return this->value + other.value;
    }

    int operator-(N& other) {
        return this->value - other.value;
    }

    void setAnnotation(const char* s) {
        memcpy(str, s, strlen(s));
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::exit(1);
    }

    N* n1 = new N(5);
    N* n2 = new N(6);
    n1->setAnnotation(argv[1]);

    // code is some kind of a function pointer
    (**(code **)*n2)(n2, s1);

    // std::cout << "Result: " << result << std::endl;

    delete n1;
    delete n2;

    return 0;
}
