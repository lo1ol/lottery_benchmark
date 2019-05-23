#include <vector>
#include <boost/container/set.hpp>
#include <boost/container/flat_set.hpp>
#include <cstdint>

namespace lottery {

template <typename Container>
class Lottery{
public:
    Lottery(const std::vector<uint64_t>& centers, const uint64_t radius);
    double GetWinAmount(uint64_t point) const;
private:
    Container m_centers;
    uint64_t m_radius;
};


template class Lottery<boost::container::set<uint64_t>>;
template class Lottery<boost::container::flat_set<uint64_t>>;
using LotterySet = Lottery<boost::container::set<uint64_t>>;
using LotteryFlatSet = Lottery<boost::container::flat_set<uint64_t>>;
}
