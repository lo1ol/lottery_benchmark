#include <algorithm>
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

LotterySet::LotterySet(const std::vector<uint64_t>& centers, const uint64_t radius)
    : m_radius(radius)
{
    if(centers.empty()) {
        throw std::invalid_argument("Empty vetctor of centers!");
    }

    m_centers.insert(centers.begin(), centers.end());
}

double LotterySet::GetWinAmount(uint64_t point) const
{
    const decltype(m_centers)::const_iterator& upper_bound = m_centers.lower_bound(point);
    const decltype(m_centers)::const_iterator& lower_bound = upper_bound == m_centers.begin() ? upper_bound : std::prev(upper_bound);
    uint64_t dist;

    if (upper_bound == m_centers.end()) {
        dist = GetDist(*upper_bound, point);
    } else {
        dist = std::min(GetDist(*lower_bound, point), GetDist(*upper_bound, point));
    }

    return lottery::GetWinAmount(dist, m_radius);
}

LotteryVector::LotteryVector(std::vector<uint64_t>&& centers, const uint64_t radius)
    : m_radius(radius)
{
    if(centers.empty()) {
        throw std::invalid_argument("Empty vetctor of centers!");
    }

    m_centers = std::move(centers);
    std::sort(m_centers.begin(), m_centers.end());
}

double LotteryVector::GetWinAmount(uint64_t point) const
{
    const decltype(m_centers)::const_iterator& upper_bound = std::lower_bound(m_centers.begin(), m_centers.end(), point);
    const decltype(m_centers)::const_iterator& lower_bound = upper_bound == m_centers.begin() ? upper_bound : std::prev(upper_bound);
    uint64_t dist;

    if (upper_bound == m_centers.end()) {
        dist = GetDist(*upper_bound, point);
    } else {
        dist = std::min(GetDist(*lower_bound, point), GetDist(*upper_bound, point));
    }

    return lottery::GetWinAmount(dist, m_radius);
}

}
