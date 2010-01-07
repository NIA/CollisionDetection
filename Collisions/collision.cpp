#include "collisions.h"
#include <algorithm>

namespace Collisions
{
    // -------------------------- H e l p e r s ------------------------------------------

    // Returns true, if first point is between second and third
    bool is_point_between(const Point &inner_point, const Point &outer_point1, const Point &outer_point2)
    {
        double squared_length = (outer_point2 - outer_point1).sqared_norm();
        return ( less_or_equal( (inner_point - outer_point1).sqared_norm(), squared_length ) &&
                 less_or_equal( (outer_point2 - inner_point).sqared_norm(), squared_length ) );
    }

    double distance_between_point_and_line(const Point &point, const Point &line_point, const Vector &line_vector,
                                           /*out*/ Point &nearest_point )
    {
        check_nonzero_vector( line_vector, InvalidLineVectorError() );

        double t = line_vector*( point - line_point) / line_vector.sqared_norm();
        Point perpendicular_base = line_point + t*line_vector;
        nearest_point = perpendicular_base;
        return distance(point, perpendicular_base);
    }

    double distance_between_point_and_segment(const Point &point, const Point &segment_start, const Point &segment_end)
    {
        check_segment( segment_start, segment_end );

        Point nearest;
        double dst = distance_between_point_and_line( point, segment_start, segment_end - segment_start, nearest );
        if( ! is_point_between( nearest, segment_start, segment_end ) )
        {
            dst = std::min( distance(point, segment_start), distance(point, segment_end) );
        }
        return dst;
    }

    // -------------------- C o l l i s i o n   f i n d e r s -----------------------------
    // All functions return true, if there is a collision, false - if none;
    // and write collision point into `collison_point', if there is any.

    bool line_and_plane_collision(const Point &line_point, const Vector &line_vector,
                                  const Point &plane_point, const Vector &plane_normal,
                                  /*out*/ Point &collision_point)
    {
        check_nonzero_vector( line_vector, InvalidLineVectorError() );
        check_nonzero_vector( plane_normal, InvalidNormalError() );

        double denominator = line_vector * plane_normal;
        if( equal(denominator, 0) )
        {
            return false;
        }
        else
        {
            double t = (plane_point - line_point)*plane_normal/denominator;
            collision_point = line_point + t*line_vector;
            return true;
        }
    }

    bool segment_and_plane_collision(const Point &segment_start, const Point &segment_end,
                                     const Point &plane_point, const Vector &plane_normal,
                                     /*out*/ Point &collision_point)
    {
        check_segment( segment_start, segment_end );
        check_nonzero_vector( plane_normal, InvalidNormalError() );

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

    bool sphere_and_plane_collision(const Point &segment_start, const Point &segment_end, double sphere_radius,
                                    const Point &plane_point, const Vector &plane_normal,
                                    /*out*/ Point &collision_point)
    {
        check_segment( segment_start, segment_end );
        check_nonzero_vector( plane_normal, InvalidNormalError() );

        Vector line_vector = segment_end - segment_start;
        Point point;
        Vector shift = ( line_vector * plane_normal > 0 ) ? sphere_radius*plane_normal : -sphere_radius*plane_normal; // lower or upper collision
        bool result = segment_and_plane_collision(segment_start + shift,
                                                  segment_end   + shift,
                                                  plane_point, plane_normal, point);
        if( result )
        {
            collision_point = point;
        }
        return result;
    }

    bool sphere_and_point_collision(const Point &segment_start, const Point &segment_end, double sphere_radius,
                                    const Point &point)
    {
        check_segment( segment_start, segment_end );

        return greater_or_equal( sphere_radius, distance_between_point_and_segment( point, segment_start, segment_end ) );
    }
};
