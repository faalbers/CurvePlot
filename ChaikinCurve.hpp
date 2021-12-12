#ifndef CURVEPLOT_CHAIKINCURVE
#define CURVEPLOT_CHAIKINCURVE

#include "CurveItem.hpp"

class ChaikinCurve : public CurveItem
{
public:
    ChaikinCurve(MH::Node *chaikinCurve);

    void    pointItemChanged(size_t itemIndex, QPointF offset);
    void    transformChanged();
    void    modelChanged();

private:
    void    createPointItems_();
    void    updateCurvePath_();

    Eigen::Array4Xd getCPPoints_() const;
    void            setCPPoints_(Eigen::Array4Xd cpPoints);
};

#endif
