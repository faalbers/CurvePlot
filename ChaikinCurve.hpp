#ifndef CURVEPLOT_CHAIKINCURVE
#define CURVEPLOT_CHAIKINCURVE

#include "CurveItem.hpp"

class ChaikinCurve : public CurveItem
{
public:
    ChaikinCurve(MH::Node *chaikinCurve);

    void    pointItemChanged();
    void    transformChanged();
    void    modelChanged();

private:
    void    createPointItems_();
    void    updateCurvePath_();
};

#endif
