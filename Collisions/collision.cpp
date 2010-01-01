#include "collisions.h"

namespace Collisions
{
    // Returns true, if first point is between second and third
    bool is_point_between(const Point &inner_point, const Point &outer_point1, const Point &outer_point2)
    {
        double squared_length = (outer_point2 - outer_point1).sqared_norm();
        return ( less_or_equal( (inner_point - outer_point1).sqared_norm(), squared_length ) &&
                 less_or_equal( (outer_point2 - inner_point).sqared_norm(), squared_length ) );
    }

    // Returns true, if there is a collision, false - if none.
    // Writes collision point into collison_point, if there is any.
    bool line_and_plane_collision(const Point &line_point, const Vector &line_vector,
                                  const Point &plane_point, const Vector &plane_normal,
                                  /*out*/ Point &collision_point)
    {
        double denominator = line_vector * plane_normal;
        if( equal(denominator, 0) )
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

    // Returns number of collision points (0, 1 or 2).
    // Writes collision point into collison_point1 and collison_point2, if there is any.    
    unsigned sphere_and_plane_collision(const Point &segment_start, const Point &segment_end, double sphere_radius,
                                        const Point &plane_point, const Vector &plane_normal,
                                        /*out*/ Point &collision_point1, Point &collision_point2)
    {
        Point point1, point2;
        bool result1 = segment_and_plane_collision(segment_start - plane_normal*sphere_radius,
                                                   segment_end   - plane_normal*sphere_radius,
                                                   plane_point, plane_normal, point1); // upper collision
        bool result2 = segment_and_plane_collision(segment_start + plane_normal*sphere_radius,
                                                   segment_end   + plane_normal*sphere_radius,
                                                   plane_point, plane_normal, point2); // lower collision
        unsigned count = 0;
        if( result1 )
        {
            collision_point1 = point1;
            ++count;
        }
        if( result2 )
        {
            if( result1 )
                collision_point2 = point2;
            else
                collision_point1 = point2;
            ++count;
        }
        return count;
    }
};
