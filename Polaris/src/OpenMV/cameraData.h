#include <cstdint>
#ifndef __CAMERADATUM_H
#define __CAMERADATUM_H

/*
 * CameraData is the data received from the camera 
 * Code Adapted from RBE 2002 D23 Repository 
*/
struct CameraData { uint16_t angleroll, anglepitch, cx, cy; };

#endif
