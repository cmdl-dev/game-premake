
#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "raylib.h"
#include <iostream>

class HealthComponent
{
public:
    HealthComponent(int health) { m_health = health; }
    void takeDamage(int dmg)
    {
        m_health -= dmg;
        std::cout << "Taking: " << dmg << " Health left: " << m_health << "\n";
    };
    bool hasDied() { return m_health <= 0; };

private:
    int m_health;
};
#endif
