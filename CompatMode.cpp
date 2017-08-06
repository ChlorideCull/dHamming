#include <array>
#include "CompatMode.hpp"
#include "Utils.hpp"
#include <cstring>
#include <tuple>

namespace Chloride {
    CompatHashList::CompatHashList() {

    }

    void CompatHashList::Add(const char *Hash) {
        std::array<std::uint64_t, 4> target;
        auto srcvec = Utils::DecodeHex(Hash);
        if (srcvec.size() != 32)
            return;
        std::memcpy(target.data(), srcvec.data(), 32);
        this->InternalVector.insert(this->InternalVector.cend(), target);
    }

    CompatHashPairs::CompatHashPairs(std::list<std::tuple<std::array<uint64_t, 4>, std::array<uint64_t, 4>>> InternalList) {
        this->InternalList = InternalList;
    }

    CompatHashPairs::~CompatHashPairs() {
    }

    const char * CompatHashPairs::GetLeft() {
        return this->Left.c_str();
    }

    const char* CompatHashPairs::GetRight() {
        return this->Right.c_str();
    }

    bool CompatHashPairs::Advance() {
        if (this->InternalList.size() == 0) {
            return false;
        }
        std::array<uint64_t, 4> intLeft;
        std::array<uint64_t, 4> intRight;
        std::tie(intLeft, intRight) = this->InternalList.front();
        this->InternalList.pop_front();

        std::vector<uint8_t> convLeft (32);
        std::memcpy(convLeft.data(), intLeft.data(), 32);
        std::vector<uint8_t> convRight (32);
        std::memcpy(convRight.data(), intRight.data(), 32);
        this->Left = Utils::EncodeHex(convLeft);
        this->Right = Utils::EncodeHex(convRight);

        return true;
    }

    CompatHashPairs::CompatHashPairs() {

    }
}