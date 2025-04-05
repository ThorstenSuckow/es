#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

struct tm *MyDate;
time_t  tim;

const char *MONTHS[12] = {
    "Januar",
    "Februar",
    "März",
    "April",
    "Mail",
    "Juni",
    "Juli",
    "August",
    "September",
    "Oktober",
    "November",
    "Dezember",
};

void pad(int cmp, char *buf) {
    buf[0] = (cmp / 10) + '0';
    buf[1] = (cmp % 10) + '0';
    buf[2] = '\0';
 }

/**
 * Pads integer values as required (leading 0s) and writes the result in buf.
 */
int padComponent(const char c, struct tm *MyDate, char *buf) {
    switch (c) {
        case 'S': pad(MyDate->tm_sec, buf); break;
        case 'M': pad(MyDate->tm_min, buf); break;
        case 'H': pad(MyDate->tm_hour, buf);break;
        case 'D': pad(MyDate->tm_mday, buf); break;
        case 'n': pad(MyDate->tm_mon, buf); break;
        case 'y': pad((MyDate->tm_year) % 100, buf);break;
        case 'Y': sprintf(buf, "%d", MyDate->tm_year + 1900);break;
        default:
            return 0;
    }

    return 1;
}

/**
 * Returns the number of expected characters in the replacement
 * for the control character c.
 */
int reqsize(char c) {
    if (c == 'Y') {
        return 4;
    }
    char *seq = "SMHDny";
    char *ptr = strchr(seq, c);
    return ptr != NULL ? 2 : 0;
}

int main(int argc, char *argv[]) {

    tim = time(NULL);
    MyDate = localtime(&tim);

    // reserve 16 Bytes for the string buffer
    char BUFFER[16];
    int CMD_LENGTH = strlen(argv[1]);

    for (int i = 0; i < CMD_LENGTH; i++) {
        char c = argv[1][i];
        if (c != '%' || i == CMD_LENGTH - 1) {
            printf("%c", c);
            continue;
        }
        char next = argv[1][i + 1];

        // Replacement-logic starts here.
        // skip one ahead
        i++;

        // string-print month-name
        if (next == 'N') {
            printf("%s", MONTHS[MyDate->tm_mon]);
            continue;
        }

        // char not in substitution list;
        // print previous and next char; this will
        // also take care of %%
        if (reqsize(next) == 0) {
            printf("%c%c", c, next);
            continue;
        }

        // pad as required, print, reset BUFFER
        padComponent(next, MyDate, BUFFER);
        printf("%s", BUFFER);
        BUFFER[0] = '\0';
    }
    printf("\n");

    return 0;
}