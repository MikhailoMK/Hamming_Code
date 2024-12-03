#ifndef HAMMING_H_INCLUDED
#define HAMMING_H_INCLUDED
#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>

using namespace std;

namespace Hamming
{
    uint8_t EncodeHelper(uint8_t byte);
    vector<uint8_t> Encode(const vector<uint8_t> bytes);
    uint8_t DecodeHelper(uint8_t x);
    vector<uint8_t> Decode(const vector<uint8_t> bytes);
}

#endif