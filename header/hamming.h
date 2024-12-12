#ifndef PARITY_CHECK_INCLUDED
#define PARITY_CHECK_INCLUDED
#include <iostream>
#include <bitset>
#include <cstdint>
#include <vector>

using namespace std;

namespace ParityCorrection
{
    uint8_t CorrectByte(uint8_t byte);

    vector<uint8_t> GenerateParityCode(const vector<uint8_t>& inputBytes);

    uint8_t RepairByte(uint8_t x);

    vector<uint8_t> RecoverData(const vector<uint8_t>& encodedBytes);
}

#endif // PARITY_CHECK_INCLUDED
