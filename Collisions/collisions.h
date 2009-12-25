#pragma once
#include "point.h"

// -------------------------- H e l p e r s ------------------------------------------

// Returns true, if first point is between second and third
bool is_point_between(Point inner_point, Point outer_point1, Point outer_point2);

// -------------------- C o l l i s i o n   f i n d e r s -----------------------------

// Returns true, if there is a collision, false - if none.
// Writes collision point into collison_point, if there is any.
bool line_and_plane_collision(Point line_point, Vector line_vector,
                              Point plane_point, Vector plane_normal,
                              /*out*/ Point &collision_point);

// Returns true, if there is a collision, false - if none.
// Writes collision point into collison_point, if there is any.
bool segment_and_plane_collision(Point segment_start, Point segment_end,
                                 Point plane_point, Vector plane_normal,
                                 /*out*/ Point &collision_point);
