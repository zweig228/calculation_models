#include "termo.h"

void calculate_temperatures(kinematic_struct &kinematic, double radius, double step)
{
    double full_velocity = magnitude(kinematic.velocity);

    // Рассчитываем параметры для каждого сегмента пули
    for (double x = 0; x <= radius; x += step) {
        // Вычисляем угол phi для текущего сегмента
        double adjacent = sqrt(radius * radius - x * x);
        double phi = atan2(x, adjacent);

        // Вычисление энтальпии торможения
        double h0 = full_velocity * full_velocity / 2 + enthalpy_inf_;

        // Энтальпия стенки
        double hw = 1000 * 300;

        // Удельный тепловой поток в точке торможения потока
        double q_sp = (1.83e-4) / sqrt(radius) * (1 - hw / h0) * sqrt(density_0_) * pow(full_velocity, 3);

        // Удельный тепловой поток в ламинарном потоке
        double q_L = 2.53e-5 * (pow(cos(phi), 0.5) * sin(phi)) / sqrt(x) * (1 - hw / h0) * sqrt(density_0_) * pow(full_velocity, 3.2);
    }

}
