#ifndef DHAMMING_LIBRARY_H
#define DHAMMING_LIBRARY_H

#include <cstdint>
#include <array>
#include <list>
#include <vector>
#include "CompatMode.hpp"

namespace Chloride {
    class dHamming {
    public:
        dHamming();

#ifndef SWIG
        std::uint32_t GetHammingDistance(const std::array<uint64_t, 4> &A, const std::array<uint64_t, 4> &B);
        std::uint32_t GetHammingDistance(const std::string &A, const std::string &B);
        std::uint32_t GetHammingDistance(const std::array<std::uint8_t, 32> &A, const std::array<std::uint8_t, 32> &B);

        std::list<std::tuple<std::array<uint64_t, 4>, std::array<uint64_t, 4>>> GetPairsOverHammingThreshold(const std::vector<std::array<uint64_t, 4>> &A, const std::uint32_t Threshold);
#endif

        // Compatibility Mode
        unsigned int GetHammingDistance(const char* A, const char* B);
        CompatHashPairs* GetPairsOverHammingThreshold(CompatHashList A, unsigned int Threshold);
    };
}

#endif