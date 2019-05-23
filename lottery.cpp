#include <stdexcept>
#include <iterator>

#include "lottery.h"

namespace lottery {

namespace {

uint64_t GetDist(const uint64_t x, uint64_t y) {
    if (x > y) {
        return x - y;
    } else {
        return y - x;
    }
}

double GetWinAmount(const uint64_t dist, const uint64_t radius)
{
    if (radius == 0 && dist == 0) {
        return 100;
    } else if (dist <= radius) {
        return 10 + (90*double(radius - dist))/radius;
    } else {
        return 0;
    }
}

}

template <typename Container>
Lottery<Container>::Lottery(const std::vector<uint64_t>& centers, const uint64_t radius)
    : m_radius(radius)
{
    if(centers.empty()) {
        throw std::invalid_argument("Empty vetctor of centers!");
    }

    m_centers.insert(centers.begin(), centers.end());
}

template <typename Container>
double Lottery<Container>::GetWinAmount(uint64_t point) const
{
    const typename Container::const_iterator& upper_bound = m_centers.lower_bound(point);
    const typename Container::const_iterator& lower_bound = upper_bound == m_centers.begin() ? upper_bound : std::prev(upper_bound);
    uint64_t dist;

    if (upper_bound == m_centers.end()) {
        dist = GetDist(*upper_bound, point);
    } else {
        dist = std::min(GetDist(*lower_bound, point), GetDist(*upper_bound, point));
    }

    return lottery::GetWinAmount(dist, m_radius);
}

}
