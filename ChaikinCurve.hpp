#ifndef CURVEPLOT_CHAIKINCURVE
#define CURVEPLOT_CHAIKINCURVE

#include "CurveItem.hpp"
#include "ModelHierarchy.hpp"

class ChaikinCurve : public CurveItem
{
public:
    ChaikinCurve(MH::Node *chaikinCurve);

    void updateCurve();
    void updateControlPoints();
    void updateCurvePath();

private:
    MH::Node    *chaikinCurveNode_;
    MH::Model   *chaikinCurveModel_;
};

#endif
