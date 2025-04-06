#include <stdio.h>
#include <stdlib.h>

#define BITMAP_SIZE 2// * 8!
#define BYTESIZE 8


unsigned char bitmap[BITMAP_SIZE];


void printBitmap(int bit_i, int set) {

    if (set == 0) {
        printf("Clearing bit %d:", bit_i);
    } else {
        printf("Setting bit %d:", bit_i);
    }

    for (int i = BITMAP_SIZE - 1; i >= 0; i--) {
        for (int j = 0; j < BYTESIZE; j++) {
            if (j % (BYTESIZE / 2) == 0) {
                printf(" ");
            }
            printf("%d", (bitmap[i] & (0x01 << (BYTESIZE - 1) - j)) ? 1 : 0);

        }
    }
    printf("\n");
}


void BitMapInit() {
    for (int i = 0; i < BITMAP_SIZE; i++) {
        bitmap[i] = 0x00;
    }
}


void _BitMapSet(int PortNbr, int value) {
    if (value != 0 && value != 1) {
        fprintf(stderr, "Unexpected value for bit: %d\n", value);
        exit(1);

    }

    int idx = PortNbr / BYTESIZE;

    if (PortNbr < 0 || idx > BITMAP_SIZE -1) {
        fprintf(stderr, "Error: PortNbr %d does not exist in range [0, %d]\n", PortNbr, BITMAP_SIZE * BYTESIZE - 1);
        exit(1);
    }

    int newbit = 0x01 << (PortNbr % 8);

    if (value == 0) {
        // 0001 0000 -> 1110 1111
        // 1110 1111 & 0101 0001 -> 0100 0001
        bitmap[idx] &= ~newbit;
    } else {
        // 0001 0000 | 0100 0001 -> 0101 0001
        bitmap[idx] |= newbit;
    }
}


void BitMapSet(int PortNbr) {
    _BitMapSet(PortNbr, 1);
}

void BitMapClear(int PortNbr) {
    _BitMapSet(PortNbr, 0);
}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Usage: BitMap bit_1 bit_2 ... bit_n, with bit_i in [0,  %d]\n", BITMAP_SIZE * BYTESIZE);
        exit(0);
    }

    BitMapInit();
    int bit_i;

    for (int i = 1; i < argc; i++) {
        if (sscanf(argv[i], "%d", &bit_i) != 1) {
            printf("no valid argument for bit_%d, skipping...\n", i - 1);
            continue;
        }

        BitMapSet(bit_i);
        printBitmap(bit_i, 1);
    }

    for (int i = 1; i < argc; i++) {
        if (sscanf(argv[i], "%d", &bit_i) != 1) {
            continue;
        }

        BitMapClear(bit_i);
        printBitmap(bit_i, 0);
    }

    return 0;
}