#ifndef CURVEPLOT_BSPLINECURVE
#define CURVEPLOT_BSPLINECURVE

#include "CurveItem.hpp"
#include "ModelHierarchy.hpp"

class BSplineCurve : public CurveItem
{
public:
    BSplineCurve(MH::Node *bsplineCurveNode);

    void updateCurve();

private:
    QPointF bezier_(double &t, int i, int j) const;
};

#endif
