#include "kinematic.h"

void recount_object_state(kinematic_struct& kinematic, double delta_t, double mass, double air_temperature, double cross_sectional_area)
{
    // Обновление текущего значения времени
    kinematic.t_act += delta_t;

    //Расчет ускорения свободного падения
    double g = g_0_ * (earth_radius_ / (earth_radius_ + kinematic.position.z)) * (earth_radius_ / (earth_radius_ + kinematic.position.z));

    //Расчет плотности воздуха на высоте полета
    double density = density_0_ * exp(-g * air_molar_mass_ * kinematic.position.z / (universal_gas_constant_ * air_temperature));

    // Расчитываем величину силы сопротивления воздуха
    double drag_force_magnitude = drag_coefficient_ * density * magnitude(kinematic.velocity) * magnitude(kinematic.velocity) * cross_sectional_area / 2.0;

    // Нормализуем вектор скорости и умножаем его на отрицательную величину силы сопротивления
    Vector3D drag_force = kinematic.velocity; // Создаем копию вектора скорости
    drag_force.normalize(); // Нормализуем копию
    drag_force = drag_force * (-drag_force_magnitude); // Умножаем нормализованный вектор на скаляр

    // Расчет вектора силы тяжести
    Vector3D gravity_force(0, 0, -mass * g);

    // Векторное уравнение пересчета скорости
    Vector3D total_force = drag_force + gravity_force;
    Vector3D acceleration = total_force / mass;
    kinematic.velocity += acceleration * delta_t;

    // Пересчет позиции
    kinematic.position += kinematic.velocity * delta_t;
}
