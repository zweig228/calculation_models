#include "init_kinematic.h"

// Инициализация состояния объекта (положение и скорость)
void object_state_initialization(kinematic_struct& kinematic, double zenith_angle, double azimuth_angle, double velocity_0, Vector3D initial_position, double sea_height)
{
    double zenith_angle_rad = zenith_angle * M_PI / 180.0;
    double azimuth_angle_rad = azimuth_angle * M_PI / 180.0;

    kinematic.t_act = 0;

    // Инициализация скорости после выстрела
    kinematic.velocity.x = velocity_0 * cos(zenith_angle_rad) * cos(azimuth_angle_rad);
    kinematic.velocity.y = velocity_0 * cos(zenith_angle_rad) * sin(azimuth_angle_rad);
    kinematic.velocity.z = velocity_0 * sin(zenith_angle_rad);

    // Инициализация положения объекта
    kinematic.position.x = initial_position.x;
    kinematic.position.y = initial_position.y;
    kinematic.position.z = initial_position.z + sea_height;
}
