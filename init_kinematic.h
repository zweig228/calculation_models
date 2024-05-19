#ifndef INIT_KINEMATIC_H
#define INIT_KINEMATIC_H

#include "termo.h"

void object_state_initialization(kinematic_struct& kinematic, double zenith_angle, double azimuth_angle, double velocity_0, Vector3D initial_position, double sea_height);

#endif // INIT_KINEMATIC_H
