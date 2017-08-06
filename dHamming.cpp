#include "dHamming.hpp"
#include "hammdist.h"
#include "Utils.hpp"
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <cstring>


namespace Chloride {
    dHamming::dHamming() {
        hammdist_init();
    };

    std::uint32_t dHamming::GetHammingDistance(const std::array<uint64_t, 4> &A, const std::array<uint64_t, 4> &B) {
        return (std::uint32_t)hamm_distance64_m(A.data(), B.data(), 4);
    };

    std::uint32_t dHamming::GetHammingDistance(const std::string &A, const std::string &B) {
        if (A.length() != 64) {
            throw std::invalid_argument("A has to be 256-bits.");
        }
        if (B.length() != 64) {
            throw std::invalid_argument("B has to be 256-bits.");
        }
        auto A_vec = Utils::DecodeHex(A);
        auto B_vec = Utils::DecodeHex(B);
        std::array<uint8_t, 32> A_raw;
        std::memcpy(A_raw.data(), A_vec.data(), A_raw.size());
        std::array<uint8_t, 32> B_raw;
        std::memcpy(B_raw.data(), B_vec.data(), B_raw.size());
        return this->GetHammingDistance(A_raw, B_raw);
    };

    std::uint32_t dHamming::GetHammingDistance(const std::array<std::uint8_t, 32> &A, const std::array<std::uint8_t, 32> &B) {
        const uint64_t* A_raw = (const uint64_t*)A.data();
        const uint64_t* B_raw = (const uint64_t*)B.data();
        return (std::uint32_t)hamm_distance64_m(A_raw, B_raw, 4);
    };

    std::list<std::tuple<std::array<uint64_t, 4>, std::array<uint64_t, 4>>> dHamming::GetPairsOverHammingThreshold(const std::vector<std::array<uint64_t, 4>> &A, const std::uint32_t Threshold) {
        std::list<std::tuple<std::array<uint64_t, 4>, std::array<uint64_t, 4>>> output;
        std::list<size_t> skipIndex;
        for (size_t master_index = 0; master_index < A.size(); ++master_index) {
            for (size_t slave_index = master_index+1; slave_index < A.size(); ++slave_index) {
                std::uint32_t hammingDistance = this->GetHammingDistance(A[master_index], A[slave_index]);
                if (hammingDistance <= Threshold) {
                    skipIndex.insert(skipIndex.cend(), slave_index);
                    output.insert(output.cend(), std::make_tuple(A[master_index], A[slave_index]));
                }
            }
        }
        return output;
    };

    // Compatibility mode below - only language features, no exceptions.
    unsigned int dHamming::GetHammingDistance(const char* A, const char* B) {
        try {
            return this->GetHammingDistance(std::string(A), std::string(B));
        } catch (std::invalid_argument) {
            return UINT32_MAX;
        }
    }

    CompatHashPairs* dHamming::GetPairsOverHammingThreshold(CompatHashList A, unsigned int Threshold) {
        auto internalList = this->GetPairsOverHammingThreshold(A.InternalVector, Threshold);
        CompatHashPairs* chp = new CompatHashPairs(internalList);
        return chp;
    }
}