#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <QString>
#include <QTextStream>
#include <cmath>

#include "geometry_sb.h"


const double g_0_ = 9.80665; // ускорение свободного падения на уровне моря, м/с²
const double earth_radius_ = 6371000; // средний радиус Земли, метры
const double density_0_ = 1.225; //плотность на уровне моря (кг/м3)
const double air_molar_mass_ = 0.029; //молярная масса воздуха (кг/моль)
const double universal_gas_constant_ = 8.314; //универсальная газовая постоянная Дж/(моль·К)
const double drag_coefficient_ = 0.05; //Коэффициент сопротивления формы для вытянутого каплевидного тела

typedef struct
{
    Vector3D velocity;
    Vector3D position;
    double t_act;
} kinematic_struct;

void recount_object_state(kinematic_struct& k, double delta_t, double mass, double air_temperature, double cross_sectional_area);

#endif /* KINEMATIC_H */
