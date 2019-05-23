#include <vector>
#include <set>
#include <cstdint>

namespace lottery {

class LotterySet{
public:
    LotterySet(const std::vector<uint64_t>& centers, const uint64_t radius);
    double GetWinAmount(uint64_t point) const;
private:
    std::set<uint64_t> m_centers;
    uint64_t m_radius;
};

class LotteryVector{
public:
    LotteryVector(const std::vector<uint64_t>& centers, const uint64_t radius)
        : LotteryVector(std::vector<uint64_t>(centers), radius)
    {}
    LotteryVector(std::vector<uint64_t>&& centers, const uint64_t radius);
    double GetWinAmount(uint64_t point) const;
private:
    std::vector<uint64_t> m_centers;
    uint64_t m_radius;
};

}
