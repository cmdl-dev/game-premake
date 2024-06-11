#include "VectorUtil.h"

Vector2 VectorUtil::AddVector(Vector2 a, Vector2 b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

bool VectorUtil::VectorEqual(Vector2 a, Vector2 b)
{
    if (a.x != b.x)
        return false;
    if (a.y != b.y)
        return false;
    return true;
}
