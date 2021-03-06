#include "collisions.h"
#include <algorithm>
#include <cmath>

namespace Collisions
{
    // -------------------------- H e l p e r s ------------------------------------------

    // Returns true, if first point is between second and third
    bool is_point_between(const Point &inner_point, const Point &outer_point1, const Point &outer_point2)
    {
        const double squared_length = (outer_point2 - outer_point1).sqared_norm();
        return ( less_or_equal( (inner_point - outer_point1).sqared_norm(), squared_length ) &&
                 less_or_equal( (outer_point2 - inner_point).sqared_norm(), squared_length ) );
    }

    double distance_between_point_and_line(const Point &point, const Point &line_point, const Vector &line_vector,
                                           /*out*/ Point &nearest_point )
    {
        check_nonzero_vector( line_vector, InvalidLineVectorError() );

        const double t = line_vector*(point - line_point) / line_vector.sqared_norm();
        const Point perpendicular_base = line_point + t*line_vector;
        nearest_point = perpendicular_base;
        return distance( point, perpendicular_base );
    }

    double distance_between_point_and_segment(const Point &point, const Point &segment_start, const Point &segment_end)
    {
        check_segment( segment_start, segment_end );

        Point nearest;
        double dst = distance_between_point_and_line( point, segment_start, segment_end - segment_start, nearest );
        if( ! is_point_between( nearest, segment_start, segment_end ) )
        {
            dst = std::min( distance( point, segment_start ), distance( point, segment_end ) );
        }
        return dst;
    }

    Point _nearest_on_parallels(const Point &line_point1, const Point &line_point2, const Vector &line_vector)
    // returns the point on first line, nearest to line_point2
    {
        const Vector L1 = line_vector.normalized();
        return line_point1 + ( (line_point2 - line_point1)*L1 )*L1; // A1 plus proection of A2-A1 onto L1
    }

    double distance_between_two_lines(const Point &line_point1, const Vector &line_vector1,
                                      const Point &line_point2, const Vector &line_vector2)
    {
        check_nonzero_vector( line_vector1, InvalidLineVectorError() );
        check_nonzero_vector( line_vector2, InvalidLineVectorError() );
        const Vector h = cross_product( line_vector1, line_vector2 ).normalized(); // perpendicular
        double dst;
        if( h.is_zero() )
        {
            // lines are parallel
            const Point H = _nearest_on_parallels( line_point1, line_point2, line_vector1 );
            dst = distance( H, line_point2 );
        }
        else
        {
            // lines are not parallel
            dst = fabs( (line_point2 - line_point1)*h ); // legth of projection of 'vector from one line to another' to the perpendicular
        }
        return dst;
    }

    void nearest_points_on_lines(const Point &line_point1, const Vector &line_vector1,
                                 const Point &line_point2, const Vector &line_vector2,
                                 /*out*/ Point &result1, Point &result2)
    {
        check_nonzero_vector( line_vector1, InvalidLineVectorError() );
        check_nonzero_vector( line_vector2, InvalidLineVectorError() );

        const Point &A1 = line_point1; // aliases
        const Point &A2 = line_point2;
        const Point &L1 = line_vector1;
        const Point &L2 = line_vector2;

        const double cross_product_sqared_norm = cross_product( L1, L2 ).sqared_norm();
        
        if( equal( 0.0, cross_product_sqared_norm ) )
        {
            // lines are parallel
            result1 = _nearest_on_parallels( line_point1, line_point2, line_vector1 );
            result2 = line_point2;
        }
        else
        {
            // lines are not parallel

            // MATH CHEAT: linear system solved by wxMaxima (see nearest_points.wxm)
            const double t1 = ( ((A2.y-A1.y)*L1.y + (A2.x-A1.x)*L1.x)*L2.z*L2.z + (((A1.y-A2.y)*L1.z + (A1.z-A2.z)*L1.y)*L2.y
                              + ((A1.x-A2.x)*L1.z + (A1.z-A2.z)*L1.x)*L2.x)*L2.z + ((A2.z-A1.z)*L1.z + (A2.x-A1.x)*L1.x)*L2.y*L2.y
                              + ((A1.x-A2.x)*L1.y + (A1.y-A2.y)*L1.x)*L2.x*L2.y + ((A2.z-A1.z)*L1.z + (A2.y-A1.y)*L1.y)*L2.x*L2.x
                              ) / cross_product_sqared_norm;
            const double t2 = ( (((A2.y-A1.y)*L1.y + (A2.x-A1.x)*L1.x)*L1.z + (A1.z-A2.z)*L1.y*L1.y + (A1.z-A2.z)*L1.x*L1.x)*L2.z
                              + ((A1.y-A2.y)*L1.z*L1.z + (A2.z-A1.z)*L1.y*L1.z + (A2.x-A1.x)*L1.x*L1.y + (A1.y-A2.y)*L1.x*L1.x)*L2.y
                              + ((A1.x-A2.x)*L1.z*L1.z + (A2.z-A1.z)*L1.x*L1.z + (A1.x-A2.x)*L1.y*L1.y + (A2.y-A1.y)*L1.x*L1.y)*L2.x
                              ) / cross_product_sqared_norm;
            // END MATH CHEAT
            result1 = A1 + t1*L1;
            result2 = A2 + t2*L2;
        }
    }

    bool is_point_inside_triangle(const Point &point, const Triangle &triangle)
    {
        // TODO: check whether the point is in the same plane as triangle.
        // By now this function returns true if the _projection_ of the point is inside triangle
        const Vector u = triangle[1] - triangle[0];
        const Vector v = triangle[2] - triangle[0];
        const Vector r = point - triangle[0];
        
        // find components of r along u and v
        const double determinant = (u*u)*(v*v) - (u*v)*(u*v);
        check( determinant != 0, DegeneratedTriangleError() );

        const double ru = ( (r*u)*(v*v) - (u*v)*(r*v) ) / determinant;
        const double rv = ( (u*u)*(r*v) - (r*u)*(u*v) ) / determinant;

        return greater_or_equal( ru, 0 ) && greater_or_equal( rv, 0 ) && less_or_equal( ru + rv, 1 );
    }

    // Returns base of perpendicular, dropped from first line to second, with given length.
    // Returns "earlier" point (looking along first line vector)
    Point perpendicular_base(const Vector &line_vector1, const Vector &line_vector2, const Point &crosspoint, double perpendicular_length)
    {
        check_nonzero_vector( line_vector1, InvalidLineVectorError() );
        check_nonzero_vector( line_vector2, InvalidLineVectorError() );

        const Vector L1 = line_vector1.normalized();
        const Vector L2 = line_vector2.normalized();
        const double cosine = L1*L2;
        const double angle = acos(cosine);
        if( equal( 0, cosine ) )
        {
            // L1 is ortogonal to L2
            return crosspoint;
        }
        else if( equal( 0, sin(angle) ) )
        {
            // L1 is parallel to L2
            throw ParallelLinesError();
        }
        else
        {
            const double distance = perpendicular_length/tan(angle);
            return crosspoint - distance*L2;
        }
    }

    // if vector pointing outside triangle, while crossing given side
    inline bool _is_vector_outside(Vector vector, Triangle triangle, unsigned side)
    {
        return vector*triangle.side_outer_normal(side) < 0;
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

        const double denominator = line_vector * plane_normal;
        if( equal( 0, denominator ) )
        {
            return false;
        }
        else
        {
            const double t = (plane_point - line_point)*plane_normal/denominator;
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
        bool result = line_and_plane_collision( segment_start, segment_end - segment_start,
                                                plane_point, plane_normal, point );
        if( result )
        {
            result = is_point_between( point, segment_start, segment_end );
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

        const Vector line_vector = segment_end - segment_start;
        const Vector shift = sign( line_vector*plane_normal )*sphere_radius*plane_normal; // shift trajectory up or down depending on whether collision is lower or upper
        Point point;
        const bool result = segment_and_plane_collision( segment_start + shift,
                                                         segment_end   + shift,
                                                         plane_point, plane_normal, point );
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

    bool sphere_and_segment_collision(const Point &sphere_segment_start, const Point &sphere_segment_end, double sphere_radius,
                                      const Point &segment_start, const Point &segment_end,
                                      /*out*/ Point &collision_point)
    {
        check_segment( segment_start, segment_end );
        check_segment( sphere_segment_start, sphere_segment_end );

        const Vector L_sphere = (sphere_segment_end - sphere_segment_start).normalized();
        const Vector L_segment = (segment_end - segment_start).normalized();
        
        Point nearest_on_sphere_way, nearest_on_segment;
        nearest_points_on_lines( sphere_segment_start, L_sphere, segment_start, L_segment, nearest_on_sphere_way, nearest_on_segment);
        
        const double dist = distance( nearest_on_sphere_way, nearest_on_segment );
        
        if( L_sphere.is_collinear_to( L_segment ) )
        {
            // when the sphere is flying in parallel to the line, it's assumed to be no collision
            return false;
        }
        
        if( greater_or_equal( sphere_radius, dist ) )
        {
            // if distance between lines is less than radius
            const double perpendicular_length = sqrt( sphere_radius*sphere_radius - dist*dist );
            Point result = perpendicular_base( L_sphere, L_segment, nearest_on_segment, perpendicular_length );

            // now check that this collision point is inside the segment
            if( !is_point_between( result, segment_start, segment_end ) )
            {
                return false;
            }

            Vector normal; // normal, aimed from L_segment to L_sphere
            if( L_sphere.is_orthogonal_to(L_segment) )
            {
                normal = - L_sphere.normalized();
            }
            else
            {
                const Vector L_segment_other = (result - nearest_on_segment).normalized();
                assert( L_segment_other == L_segment || L_segment_other == -L_segment );
                // calculating normal, aimed from L_segment to L_sphere as double cross-product. L_segment_other is used instead of L_segment in order to avoid sign mess
                normal = cross_product( cross_product( L_sphere, L_segment_other ), L_segment_other ).normalized();
            }
            assert( !normal.is_zero() );
            Point sphere_center = result + perpendicular_length*normal + (nearest_on_sphere_way - nearest_on_segment); // sphere center is here at the moment of collision

            // now check that sphere center at the moment of collision is inside the segment
            if( !is_point_between( sphere_center, sphere_segment_start, sphere_segment_end ) )
            {
                return false;
            }

            // all checks passed => there is a collision
            collision_point = result;
            return true;
        }
        else
        {
            // otherwise, sphere flies too far, no collision
            return false;
        }
    }

    bool sphere_and_triangle_collision(const Point &segment_start, const Point &segment_end, double sphere_radius, const Triangle &triangle,
                                       /*out*/ Point &collision_point)
    {
        check_segment( segment_start, segment_end );
        const Vector L_sphere = segment_end - segment_start;
        
        // 1) is it touching a plane of triangle?
        Point result_point;
        bool result = sphere_and_plane_collision( segment_start, segment_end, sphere_radius, triangle[0], triangle.normal(), result_point );
        if( result )
        {
            // 1.1) is touching point really inside triangle
            if( is_point_inside_triangle( result_point, triangle ) )
            {
                collision_point = result_point;
                return true;
            }
        }
        
        // 2) if not, is it touching any side of triangle?
        bool any_result = false; // will be true, if there is a collision with at least one side
        Point best_result_point; // best point is the point, nearest to the start of sphere's way
        for( unsigned i = 0; i < 3; ++i )
        {
            result = sphere_and_segment_collision( segment_start, segment_end, sphere_radius,
                                                   triangle[i], triangle[ (i+1)%3 ], result_point );
            if( result && _is_vector_outside( L_sphere, triangle, i ) )
            {
                // if there is a collision, and sphere is moving inside, not outside
                if( !any_result || distance( best_result_point, segment_start ) > distance( result_point, segment_start ) )
                {
                    // if no best result, or if the best result is worst than current
                    best_result_point = result_point;
                }
                any_result = true;
            }
        }
        if( any_result )
        {
            collision_point = best_result_point;
            return true;
        }

        // 3) if not, is it touching any vertex of triangle?
        any_result = false;
        for( unsigned i = 0; i < 3; ++i )
        {
            result = sphere_and_point_collision( segment_start, segment_end, sphere_radius, triangle[i] );
            if( result &&  _is_vector_outside( L_sphere, triangle, i ) && _is_vector_outside( L_sphere, triangle, (i+2)%3 ) )
            {
                if( !any_result || distance( best_result_point, segment_start ) > distance( triangle[i], segment_start ) )
                {
                    // if no best result, or if the best result is worst than current
                    best_result_point = triangle[i];
                }
                any_result = true;
            }
        }
        if( any_result )
        {
            collision_point = best_result_point;
            return true;
        }
        return false;
    }
};
