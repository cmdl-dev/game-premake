#include "Util.h"

Vector2 Util::GetAdjustedVectorFromCollision(Hitbox *collisionBox, std::vector<std::string> groups, Vector2 calculatedVector)
{
    if (groups.empty())
        return calculatedVector;

    Vector2 adjustedVector = calculatedVector;
    Rectangle futurePosition = collisionBox->getRect();
    std::vector<Hitbox *> boxes = CollisionBoxManager::GetCollisionBoxesFor(groups);

    futurePosition.x += calculatedVector.x;
    for (Hitbox *cBox : boxes)
    {
        if (cBox->didCollideWith(futurePosition))
        {
            if (calculatedVector.x > 0.0f)
            {
                calculatedVector.x = (cBox->getRect().x - collisionBox->getRect().width) - collisionBox->getRect().x;
            }
            else if (calculatedVector.x < 0.0f)
            {
                calculatedVector.x = (cBox->getRect().x + cBox->getRect().width) - collisionBox->getRect().x;
            }
        }
    }
    // Set future x position to rosolved posiion x
    futurePosition.x = collisionBox->getRect().x + calculatedVector.x;

    futurePosition.y += calculatedVector.y;
    for (Hitbox *cBox : boxes)
    {
        if (cBox->didCollideWith(futurePosition))
        {
            if (calculatedVector.y > 0.0f)
            {
                calculatedVector.y = (cBox->getRect().y - collisionBox->getRect().height) - collisionBox->getRect().y;
            }
            else if (calculatedVector.y < 0.0f)
            {
                calculatedVector.y = (cBox->getRect().y + cBox->getRect().height) - collisionBox->getRect().y;
            }
        }
    }
    return calculatedVector;
}