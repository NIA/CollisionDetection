#pragma once
#include "point.h"
#include "floating_point.h"

namespace Collisions
{
    // -------------------------- H e l p e r s ------------------------------------------

    // Returns true, if first point is between second and third
    bool is_point_between(const Point &inner_point, const Point &outer_point1, const Point &outer_point2);

    // -------------------- C o l l i s i o n   f i n d e r s -----------------------------

    // Returns true, if there is a collision, false - if none.
    // Writes collision point into collison_point, if there is any.
    bool line_and_plane_collision(const Point &line_point, const Vector &line_vector,
                                  const Point &plane_point, const Vector &plane_normal,
                                  /*out*/ Point &collision_point);

    // Returns true, if there is a collision, false - if none.
    // Writes collision point into collison_point, if there is any.
    bool segment_and_plane_collision(const Point &segment_start, const Point &segment_end,
                                     const Point &plane_point, const Vector &plane_normal,
                                     /*out*/ Point &collision_point);
};
