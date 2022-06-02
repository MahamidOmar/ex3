

#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H
#include <iostream>

class HealthPoints
{
public:
    /*
     * constructor for HealthPoints
     */
    HealthPoints(int points = 100);

    /*
     * default destructor for HealthPoints
     */
    ~HealthPoints() = default;

    /*
     * default copy constructor for HealthPoints
     */
    HealthPoints(const HealthPoints& h) = default;

    /*
     * default operator= for HealthPoints
     */
    HealthPoints& operator=(const HealthPoints& h) = default;

    /*
     * class for errors when intering an invalid argument
     */
    class InvalidArgument {};

    /*
     * arithmetic operators for HealthPoints
     */
    HealthPoints& operator-=(const int points) ;
    HealthPoints& operator+=(const int points) ;
    HealthPoints operator+(const int points) const;
    HealthPoints operator-(const int points) const;
    friend HealthPoints operator+(const int points, const HealthPoints& h1);
    friend HealthPoints operator-(const int points, const HealthPoints& h1);



    /*
     * logical operators for Health Points for comparison
     */
    friend bool operator==(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator!=(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator<=(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator>=(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator<(const HealthPoints& h1, const HealthPoints& h2);
    friend bool operator>(const HealthPoints& h1, const HealthPoints& h2);

    /*
     * printing operators for HealthPoints
     */
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& h);


private:
    int m_healthPoints;
    int m_maxHp;

};

#endif //HEALTHPOINTS_H
