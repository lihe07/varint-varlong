#include "library.h"
#include <iostream>
#include "bitset"
using namespace std;
static const unsigned long long N1 = 128; // 2 ^ 7
static const unsigned long long N2 = 16384;
static const unsigned long long N3 = 2097152;
static const unsigned long long N4 = 268435456;
static const unsigned long long N5 = 34359738368;
static const unsigned long long N6 = 4398046511104;
static const unsigned long long N7 = 562949953421312;
static const unsigned long long N8 = 72057594037927936;
static const unsigned long long N9 = 9223372036854775808U;



int varlong_encoding_length(unsigned long long int n) {
    return (n < N1 ? 1
        : n < N2 ? 2
        : n < N3 ? 3
        : n < N4 ? 4
        : n < N5 ? 5
        : n < N6 ? 6
        : n < N7 ? 7
        : n < N8 ? 8
        : n < N9 ? 9
        :         10
        );
}
int varint_encoding_length(signed long long int signed_n) {
    auto n = (unsigned long long)signed_n;
    return (n < N1 ? 1
    : n < N2 ? 2
    : n < N3 ? 3
    : n < N4 ? 4
    :          5
    );
}


void varint_encode(unsigned int unsignedInt, unsigned char *ptr) {
    while (unsignedInt & ~0x7FL)
    {
        *(ptr++) = (unsignedInt & 0b01111111) | 0b10000000;
        unsignedInt = unsignedInt >> 7;
    }
    *ptr = unsignedInt;
}

void varlong_encode(unsigned long long int unsignedLong, unsigned char *ptr) {
    while (unsignedLong & ~0x7FL)
    {
        *(ptr++) = (unsignedLong & 0b01111111) | 0b10000000;
        unsignedLong = unsignedLong >> 7;
    }
    *ptr = unsignedLong;
}

unsigned int varint_decode(const unsigned char varint[]) {
    unsigned int normalInt = 0;
    int i = 0;
    while ((0b10000000 & varint[i]) == 0b10000000) {
        normalInt += (varint[i] & 0b01111111) << (i*7);
        i++;
    }
    normalInt += (varint[i] & 0b01111111) << (i*7);
    return normalInt;
}

unsigned long long int varlong_decode(const unsigned char varlong[]) {
    unsigned long long int normalLong = 0;
    int i = 0;
    while ((0b10000000 & varlong[i]) == 0b10000000) {
        normalLong += (varlong[i] & 0b01111111) << (i*7);
        i++;
    }
    normalLong += (varlong[i] & 0b01111111) << (i*7);
    return normalLong;
}


int main() {
    cout << "==== Debug Started ====" << endl;
    unsigned int origin = 114514;
    unsigned char varint[varint_encoding_length(origin)];
    varint_encode(origin, varint);
    cout << "origin uint:" << origin << endl;
    cout << "varint size:" << sizeof(varint)  <<  endl;
    for (int i = 0; i < sizeof(varint); ++i) {
        cout << (int)varint[i] << "/" << bitset<8>(varint[i]) << " ";
    }
    cout << endl;

    cout << "decoded: " << varint_decode(varint) << endl;

    unsigned long long int lOrigin = 1919810;
    unsigned char varlong[varlong_encoding_length(lOrigin)];
    varlong_encode(lOrigin, varlong);
    cout << "origin ulong:" << lOrigin << endl;
    cout << "varlong size:" << sizeof(varlong)  <<  endl;
    for (int i = 0; i < sizeof(varlong); ++i) {
        cout << (int)varlong[i] << "/" << bitset<8>(varlong[i]) << " ";
    }
    cout << endl;

    cout << "decoded: " << varlong_decode(varlong) << endl;

    return 0;
};
