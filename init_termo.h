#ifndef INIT_TERMO_H
#define INIT_TERMO_H

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QString>

#include "geometry_sb.h"
#include "termo.h"

bool readSegmentsFromFile(const QString &filePath, SegmentsData &segmentsData);
RingSegment convertSegmentsDataToRingSegment(const SegmentsData& segmentsData);

#endif // INIT_TERMO_H
