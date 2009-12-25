#include "collisions.h"

// returns true, if there is a collision, false - if none.
bool line_and_plane_collision(Point line_point, Vector line_vector,
                              Point plane_point, Vector plane_normal,
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

bool is_point_between(Point inner_point, Point outer_point1, Point outer_point2)
{
    double squared_length = (outer_point2 - outer_point1).sqared_norm();
    return ( (inner_point - outer_point1).sqared_norm() <= squared_length &&
             (outer_point2 - inner_point).sqared_norm() <= squared_length );
}

bool segment_and_plane_collision(Point segment_start, Point segment_end,
                                 Point plane_point, Vector plane_normal,
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
