#ifndef RING_OBJECT_MANAGER_H
#define RING_OBJECT_MANAGER_H

#include "kinematic.h"
#include "termo.h"
#include "init_kinematic.h"
#include "init_termo.h"

class ring_object_manager
{
public:
    kinematic_struct kinematic;
    RingSegment ringSegment;
    SegmentsData segmentsData;

};

#endif // RING_OBJECT_MANAGER_H
