#ifndef CURVEPLOT_BSPLINECURVE
#define CURVEPLOT_BSPLINECURVE

#include "CurveItem.hpp"

class BSplineCurve : public CurveItem
{
public:
    BSplineCurve(MH::Node *bsplineCurveNode);

    void    createPointItems();

    void    pointItemChanged(size_t itemIndex, QPointF offset);
    void    transformChanged();
    void    modelChanged();

private:
    void    createPointItems_();
    void    updateCurvePath_();

    Eigen::Array4Xd getCPPoints_() const;
    void            setCPPoints_(Eigen::Array4Xd cpPoints);
    //Eigen::Array4Xd getPointItemArray_();
};

#endif
