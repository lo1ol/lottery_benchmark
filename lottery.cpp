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
        return 10 + (90*double(radius - dist))/radius; // соблюдение пропорций. получаемые значения начинаются с 10, а прибавляемое значение являются долью от 90 в зависимости от растояния
    } else {
        return 0;
    }
}

}

template <typename Container>
Lottery<Container>::Lottery(const std::vector<uint64_t>& centers, const uint64_t radius)
    : m_radius(radius)
{
    if(centers.empty()) { // если передали пустой контейнер, то бросаем исключение
        throw std::invalid_argument("Empty vetctor of centers!");
    }

    m_centers.insert(centers.begin(), centers.end()); // в случае валидности аргументов заполняем контейнер
}

template <typename Container>
double Lottery<Container>::GetWinAmount(uint64_t point) const
{
    const typename Container::const_iterator& upper_bound = m_centers.upper_bound(point); // определяем верхнюю границу подходящего значения (метод upper_bound возвращает первый итератор, указывающий на элемент больше запрошенного)
    const typename Container::const_iterator& lower_bound = upper_bound == m_centers.begin() ? upper_bound : std::prev(upper_bound); // перед ним находится нижняя граница (если самый элемент больше чем переданный не яввляется началом)
    uint64_t dist;

    if (upper_bound == m_centers.end()) { // если верхняя граница не найдена, то проверяем только нижнюю границу
        dist = GetDist(*lower_bound, point);
    } else { // иначе берем минимум от растояний
        dist = std::min(GetDist(*lower_bound, point), GetDist(*upper_bound, point));
    }

    return lottery::GetWinAmount(dist, m_radius); // вычисляем значение выигрыша и возвращаем кго
}

}
