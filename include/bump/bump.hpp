#ifndef BUMP_TYPES_HPP_
#define BUMP_TYPES_HPP_

namespace bump
{
struct Vector2d {
    double x;
    double y;

    /**
     * @brief Vector arithmetic.
     */
    Vector2d operator+(const Vector2d& rhs) const;
    Vector2d operator-(const Vector2d& rhs) const;
    double dot(const Vector2d& rhs) const;
};

struct Box2d {
    Vector2d center;     // center of the box
    Vector2d dim;        // dimensions x & y
    double orientation;  // orientation from x-axis in radians
};

}  // namespace bump

#endif  // BUMP_TYPES_HPP_
