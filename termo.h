#ifndef TERMO_H
#define TERMO_H

#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "kinematic.h"

const double enthalpy_inf_ = 2.3e5;

const int max_number_of_segments_ = 9;

typedef struct
{
    int count;
    float radius[max_number_of_segments_];
    double offsets[max_number_of_segments_]; //смещение по оси
    double temperatures[max_number_of_segments_];
} SegmentsData;

typedef struct
{
    int num_segments;
    double alpha[max_number_of_segments_];
    double length[max_number_of_segments_];  // Длина боковой поверхности(всхе гипотенуз)
    //double visible_area[max_number_of_segments_];
} RingSegment;


void calculate_temperatures(kinematic_struct &k, double radius, double step);


#endif // TERMO_H
