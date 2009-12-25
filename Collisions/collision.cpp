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
