#ifndef BUMP_TYPES_HPP_
#define BUMP_TYPES_HPP_

namespace bump
{
struct Vector2d {
    double x = 0.0;
    double y = 0.0;

    /**
     * @brief Vector arithmetic.
     */
    Vector2d operator+(const Vector2d& rhs) const;
    Vector2d operator-(const Vector2d& rhs) const;
    Vector2d operator*(double factor) const;
    Vector2d operator/(double divisor) const;
    double dot(const Vector2d& rhs) const;
};

struct Box2d {
    Vector2d center;           // center of the box
    Vector2d dim;              // dimensions x & y
    double orientation = 0.0;  // orientation from x-axis in radians

    /**
     * @brief Check intersection with another 2D box.
     *
     * @param other box
     * @param margin to extend this box's dimensions at both ends
     * @return true if the boxes intersect, false otherwise
     */
    bool intersects(const Box2d& other, double margin = 0.0) const;
};

namespace utils
{
/**
 * @brief Create a unit vector with the giver orientation.
 *
 * @param orientation from x-axis in radians
 * @return Vector2d unit vector
 */
Vector2d createUnitVector(double orientation);

}  // namespace utils

}  // namespace bump

#endif  // BUMP_TYPES_HPP_
