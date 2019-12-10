#include <cmath>
#include <vector>

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

Vector2d Vector2d::operator*(double factor) const
{
    return {this->x * factor, this->y * factor};
}

Vector2d Vector2d::operator/(double divisor) const
{
    return {this->x / divisor, this->y / divisor};
}

bool Box2d::intersects(const Box2d& other, double margin) const
{
    // reference implementation from
    // https://www.jkh.me/files/tutorials/Separating%20Axis%20Theorem%20for%20Oriented%20Bounding%20Boxes.pdf

    // generate the candidate separating axes
    std::vector<Vector2d> candidateSeparatingAxes;
    Vector2d thisLocalX = utils::createUnitVector(this->orientation);
    Vector2d thisLocalY = {thisLocalX.y, -thisLocalX.x};
    candidateSeparatingAxes.push_back(thisLocalX);
    candidateSeparatingAxes.push_back(thisLocalY);
    Vector2d otherLocalX = utils::createUnitVector(other.orientation);
    Vector2d otherLocalY = {otherLocalX.y, -otherLocalX.x};
    candidateSeparatingAxes.push_back(otherLocalX);
    candidateSeparatingAxes.push_back(otherLocalY);

    // check if the candidate axis is a separating axis
    auto isAxisSeparating = [&](const Vector2d& axis) {
        Vector2d centerToCenter = other.center - this->center;
        double centerToCenterProj = std::abs(centerToCenter.dot(axis));

        double thisHalfDimX = (this->dim.x / 2.0) + margin;
        double thisHalfDimY = (this->dim.y / 2.0) + margin;
        double thisHalfDimXProj = std::abs((thisLocalX * thisHalfDimX).dot(axis));
        double thisHalfDimYProj = std::abs((thisLocalY * thisHalfDimY).dot(axis));

        double otherHalfDimX = (other.dim.x / 2.0);
        double otherHalfDimY = (other.dim.y / 2.0);
        double otherHalfDimXProj = std::abs((otherLocalX * otherHalfDimX).dot(axis));
        double otherHalfDimYProj = std::abs((otherLocalY * otherHalfDimY).dot(axis));

        double sumProjections = thisHalfDimXProj + thisHalfDimYProj + otherHalfDimXProj + otherHalfDimYProj;
        return centerToCenterProj > sumProjections;
    };
    for (const Vector2d& axis : candidateSeparatingAxes) {
        if (isAxisSeparating(axis)) {
            // the boxes do not intersect if there is at least one separating axis
            return false;
        }
    }
    return true;
}

namespace utils
{
Vector2d createUnitVector(double orientation)
{
    return {std::cos(orientation), std::sin(orientation)};
}

}  // namespace utils

}  // namespace bump
