

#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H
#include <iostream>

class HealthPoints
{
public:
    HealthPoints(int points = 100);
    ~HealthPoints() = default;
    HealthPoints(const HealthPoints& h) = default;
    HealthPoints& operator=(const HealthPoints& h) = default;

    class InvalidArgument {};

    HealthPoints& operator-=(const int points) ;
    HealthPoints& operator+=(const int points) ;
    HealthPoints operator+(const int points) const;
    HealthPoints operator-(const int points) const;
    friend HealthPoints operator+(const int points, const HealthPoints& h1);
    friend HealthPoints operator-(const int points, const HealthPoints& h1);



    friend bool operator==(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator!=(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator<=(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator>=(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator<(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator>(const HealthPoints& h1, const HealthPoints& h2);

    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& h);


private:
    int m_healthPoints;
    int m_maxHp;

};

#endif //HEALTHPOINTS_H
