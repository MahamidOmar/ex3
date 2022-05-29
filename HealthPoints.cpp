
#include "HealthPoints.h"
HealthPoints::HealthPoints(int points): m_healthPoints(points), m_maxHp(points)
{
    if(points <= 0)
    {
        throw HealthPoints::InvalidArgument();
    }
}

HealthPoints& HealthPoints::operator-=(const int points)
{
    m_healthPoints -= points;
    if(m_healthPoints > m_maxHp)
    {
        m_healthPoints = m_maxHp;
    }
    else if(m_healthPoints < 0)
    {
        m_healthPoints = 0;
    }
    return *this;
}
HealthPoints& HealthPoints::operator+=(const int points)
{
    (*this) -= ((-1) * points);
    return *this;
}
HealthPoints HealthPoints::operator+(const int points) const
{
    HealthPoints result(*this);
    return (result += points);
}
HealthPoints HealthPoints::operator-(const int points) const
{
    HealthPoints result(*this);
    return (result -= points);
}
HealthPoints operator+(const int points, const HealthPoints& h1)
{
    HealthPoints result(h1);
    return (result += points);
}
HealthPoints operator-(const int points, const HealthPoints& h1)
{
    HealthPoints result(h1);
    return (result -= points);
}



bool operator==(const HealthPoints& h1, const HealthPoints& h2)
{
    return h1.m_healthPoints == h2.m_healthPoints;
}
bool operator!=(const HealthPoints& h1, const HealthPoints& h2)
{
    return !(h1 == h2);
}
bool operator<=(const HealthPoints& h1, const HealthPoints& h2)
{
    return (h1 < h2) || (h1 == h2);
}
bool operator>=(const HealthPoints& h1, const HealthPoints& h2)
{
    return !(h1 < h2);
}
bool operator<(const HealthPoints& h1, const HealthPoints& h2)
{
    return h1.m_healthPoints < h2.m_healthPoints;
}
bool operator>(const HealthPoints& h1, const HealthPoints& h2)
{
    return (h1 >= h2) && (h1 != h2);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& h)
{
    os << h.m_healthPoints << "(" << h.m_maxHp << ")";
    return os;
}



