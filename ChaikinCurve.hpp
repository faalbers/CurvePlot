#ifndef CURVEPLOT_CHAIKINCURVE
#define CURVEPLOT_CHAIKINCURVE

#include "CurveItem.hpp"

class ChaikinCurve : public CurveItem
{
public:
    ChaikinCurve(MH::Node *chaikinCurve, MH::Node *cameraNode);

    void    pointItemChanged(size_t itemIndex, QPointF offset);
    void    transformChanged();
    void    modelChanged();

private:
    void    createPointItems_();
    void    updateCurvePath_();
};

#endif
