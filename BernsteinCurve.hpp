#ifndef CURVEPLOT_BernsteinCURVE
#define CURVEPLOT_BernsteinCURVE

#include "CurveItem.hpp"

class BernsteinCurve : public CurveItem
{
public:
    BernsteinCurve();

    void updateCurve();
};

#endif
