#ifndef DHAMMING_COMPATMODE_H
#define DHAMMING_COMPATMODE_H
#include <vector>
#include <list>
#include <cstdint>

namespace Chloride {
    class CompatHashList {
    public:
#ifndef SWIG
        std::vector<std::array<std::uint64_t, 4>> InternalVector;
#endif
        CompatHashList();
        void Add(const char* Hash);
    };

    class CompatHashPairs {
    private:
#ifndef SWIG
        std::list<std::tuple<std::array<uint64_t, 4>, std::array<uint64_t, 4>>> InternalList;
        std::string Left;
        std::string Right;
#endif
    public:
        CompatHashPairs();
#ifndef SWIG
        CompatHashPairs(std::list<std::tuple<std::array<uint64_t, 4>, std::array<uint64_t, 4>>> InternalList);
#endif
        ~CompatHashPairs();
        const char * GetLeft();
        const char * GetRight();
        bool Advance();
    };
}

#endif //DHAMMING_COMPATMODE_H
