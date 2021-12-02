#ifndef CURVEPLOT_BEZIERCURVE
#define CURVEPLOT_BEZIERCURVE

#include "CurveItem.hpp"

class BezierCurve : public CurveItem
{
public:
    BezierCurve(int controlPointNum_);

    void updateCurve();

private:
    QPointF bezier_(double &t, int i, int j) const;
};

#endif
