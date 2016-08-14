#ifndef LEDDETECT_H
#define LEDDETECT_H

#include "led/base.h"

int contour(const Mat src,
                Point2f &goal,
                Mat &result);
void lowExposureWAWA(const Mat src,Mat &result,Point2f &goal, bool &find_object, bool &WAWA);

#endif // LEDDETECT_H
