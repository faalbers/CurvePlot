#ifndef CURVEPLOT_BSPLINECURVE
#define CURVEPLOT_BSPLINECURVE

#include "CurveItem.hpp"

class BSplineCurve : public CurveItem
{
public:
    BSplineCurve(MH::Node *bsplineCurveNode, MH::Node *cameraNode);

    void    pointItemChanged(size_t itemIndex, QPointF offset);
    void    transformChanged();
    void    modelChanged();

    void    createPointItems();

private:
    void    createPointItems_();
    void    updateCurvePath_();

    Eigen::Array4Xd getCPPoints_() const;
    void            setCPPoints_(Eigen::Array4Xd cpPoints);
};

#endif
