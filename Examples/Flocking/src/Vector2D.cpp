#include "Vector2D.h"

namespace Flocking {
Vector2D::Vector2D(double xx, double yy) : x{xx}, y{yy} {};

void Vector2D::Normalize()
{
    double ell = Magnitude();
    if (ell > 0)
    {
        (*this) *= ((double)1)/ell;
    }
};

ostream& operator<<(ostream& os, const Vector2D &p)
{
    return os<<"["<<p.x<<","<<p.y<<"]";
};
}