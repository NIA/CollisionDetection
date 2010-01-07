#pragma once
#include "errors.h"
#include "point.h"
#include "floating_point.h"

namespace Collisions
{
    // -------------------------- H e l p e r s ------------------------------------------

    // Returns true, if first point is between second and third
    bool is_point_between(const Point &inner_point, const Point &outer_point1, const Point &outer_point2);

    double distance_between_point_and_line(const Point &point, const Point &line_point, const Vector &line_vector,
                                           /*out*/ Point &nearest_point);

    double distance_between_point_and_segment(const Point &point, const Point &segment_start, const Point &segment_end);

    // -------------------- C o l l i s i o n   f i n d e r s -----------------------------
    // All functions return true, if there is a collision, false - if none;
    // and write collision point into `collison_point', if there is any.

    bool line_and_plane_collision(const Point &line_point, const Vector &line_vector,
                                  const Point &plane_point, const Vector &plane_normal,
                                  /*out*/ Point &collision_point);

    bool segment_and_plane_collision(const Point &segment_start, const Point &segment_end,
                                     const Point &plane_point, const Vector &plane_normal,
                                     /*out*/ Point &collision_point);

    bool sphere_and_plane_collision(const Point &segment_start, const Point &segment_end, double sphere_radius,
                                    const Point &plane_point, const Vector &plane_normal,
                                    /*out*/ Point &collision_point);

    bool sphere_and_point_collision(const Point &segment_start, const Point &segment_end, double sphere_radius,
                                    const Point &point);
};
