#pragma once
#include "point.h"

// returns true, if there is a collision, false - if none.
bool line_and_plane_collision(Point line_point, Vector line_vector,
                              Point plane_point, Vector plane_normal,
                              /*out*/ Point &collision_point);
