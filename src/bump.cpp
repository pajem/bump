#include "bump/bump.hpp"

namespace bump
{
Vector2d Vector2d::operator+(const Vector2d& rhs) const
{
    return {this->x + rhs.x, this->y + rhs.y};
}

Vector2d Vector2d::operator-(const Vector2d& rhs) const
{
    return {this->x - rhs.x, this->y - rhs.y};
}

double Vector2d::dot(const Vector2d& rhs) const
{
    return (this->x * rhs.x) + (this->y * rhs.y);
}

}  // namespace bump
