#include "init_termo.h"

bool readSegmentsFromFile(const QString &filePath, SegmentsData &segmentsData)
{
    qDebug() << "Current working directory:" << QDir::currentPath();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file for reading:" << filePath;
        return false;
    }
    QTextStream in(&file);
    QString line;
    bool ok;

    // Считываем количество сегментов
    line = in.readLine();
    segmentsData.count = line.toInt(&ok);
    if (!ok || segmentsData.count <= 0 )
    {
        qDebug() << "Error parsing number of segments or number of segments out of range";
        return false;
    }
    qDebug() << "Segments count" << segmentsData.count;

    // Считываем данные каждого сегмента
    for (int i = 0; i < segmentsData.count; ++i)
    {
        line = in.readLine();
        QStringList values = line.split(' ', QString::SkipEmptyParts);
        if (values.size() != 3)
        {
            qDebug() << "Error parsing segment data, incorrect number of values at segment" << i + 1;
            return false;
        }

        // Считываем радиус
        segmentsData.radius[i] = values.at(0).toDouble(&ok);
        if (!ok)
        {
            qDebug() << "Error parsing radius at segment" << i + 1;
            return false;
        }

        // Считываем смещение
        segmentsData.offsets[i] = values.at(1).toDouble(&ok);
        if (!ok)
        {
            qDebug() << "Error parsing offset at segment" << i + 1;
            return false;
        }

        // Считываем температуру
        segmentsData.temperatures[i] = values.at(2).toDouble(&ok);
        if (!ok)
        {
            qDebug() << "Error parsing temperature at segment" << i + 1;
            return false;
        }

        // Выводим считанные данные для дебага
        qDebug()
            << "Segment" << i + 1 << ": radius =" << segmentsData.radius[i]
            << ", offset =" << segmentsData.offsets[i]
            << ", temperature =" << segmentsData.temperatures[i];
    }

    return true;
}


RingSegment convertSegmentsDataToRingSegment(const SegmentsData& segmentsData)
{
    RingSegment ringSegment;
    ringSegment.num_segments = segmentsData.count;

    double total_length = 0.0;
    double act_length [segmentsData.count];

    for (int i = 0; i < segmentsData.count; ++i)
    {
        // Вычисляем разницу радиусов для текущего и предыдущего сегментов
        double radius_difference = i == 0 ? segmentsData.radius[i] : segmentsData.radius[i] - segmentsData.radius[i - 1];

        // Вычисляем длину гипотенузы (length) прямоугольного треугольника
        ringSegment.length[i] = sqrt(pow(radius_difference, 2) + pow(segmentsData.offsets[i], 2));

        // К актуальной длине прибавляем половину текущей гипотенузы
        act_length[i] +=  ringSegment.length[i]/ 2.0;

        //Полная длина
        total_length +=  ringSegment.length[i];

        // Вычисляем угол alpha (в радианах) между нижним катетом (offset) и гипотенузой (length)
        ringSegment.alpha[i] = atan2(radius_difference, segmentsData.offsets[i]);

        qDebug() << "Segment" << i + 1 << ":"
                 << "Radius difference =" << radius_difference
                 << "Act_length =" << act_length[i]
                 << "Length =" << ringSegment.length[i]
                 << "Alpha (radians) =" << ringSegment.alpha[i]
                 << "Alpha (degrees) =" << (ringSegment.alpha[i] * 180.0 / M_PI);
    }

    qDebug() << "Total length:" << total_length;

    return ringSegment;
}
