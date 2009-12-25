#include "collisions.h"

// Returns true, if first point is between second and third
bool is_point_between(const Point &inner_point, const Point &outer_point1, const Point &outer_point2)
{
    double squared_length = (outer_point2 - outer_point1).sqared_norm();
    return ( (inner_point - outer_point1).sqared_norm() <= squared_length &&
             (outer_point2 - inner_point).sqared_norm() <= squared_length );
}

// Returns true, if there is a collision, false - if none.
// Writes collision point into collison_point, if there is any.
bool line_and_plane_collision(const Point &line_point, const Vector &line_vector,
                              const Point &plane_point, const Vector &plane_normal,
                              /*out*/ Point &collision_point)
{
    double denominator = line_vector * plane_normal;
    if( denominator == 0 ) // TODO: normal floating-point comparison
    {
        return false;
    }
    else
    {
        double t = (plane_point - line_point)*plane_normal/denominator;
        collision_point = line_point + line_vector*t;
        return true;
    }
}

// Returns true, if there is a collision, false - if none.
// Writes collision point into collison_point, if there is any.
bool segment_and_plane_collision(const Point &segment_start, const Point &segment_end,
                                 const Point &plane_point, const Vector &plane_normal,
                                 /*out*/ Point &collision_point)
{
    Point point;
    bool result = line_and_plane_collision(segment_start, segment_end - segment_start,
                                           plane_point, plane_normal, point);
    if( result )
    {
        result = is_point_between(point, segment_start, segment_end);
        if( result )
        {
            collision_point = point;
        }
    }
    return result;
}
