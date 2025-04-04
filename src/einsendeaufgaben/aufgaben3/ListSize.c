 #include <stdio.h>

void main() {

    printf("%18s (%zu)\n", "short",          sizeof(short));
    printf("%18s (%zu)\n", "unsigned short", sizeof(unsigned short));
    printf("%18s (%zu)\n", "signed short",   sizeof(signed short));

    printf("%18s (%zu)\n", "int",          sizeof(int));
    printf("%18s (%zu)\n", "signed int",   sizeof(signed int));
    printf("%18s (%zu)\n", "unsigned int", sizeof(unsigned int));

    printf("%18s (%zu)\n", "long",          sizeof(long));
    printf("%18s (%zu)\n", "unsigned long", sizeof(unsigned long));
    printf("%18s (%zu)\n", "signed long",   sizeof(signed long));

    printf("%18s (%zu)\n", "long long",          sizeof(long long));
    printf("%18s (%zu)\n", "unsigned long long", sizeof(unsigned long long));
    printf("%18s (%zu)\n", "signed long long",   sizeof(signed long long));

    printf("%18s (%zu)\n", "float",       sizeof(float));
    printf("%18s (%zu)\n", "double",      sizeof(double));
    printf("%18s (%zu)\n", "long double", sizeof(long double));
}