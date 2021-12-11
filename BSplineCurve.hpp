#ifndef CURVEPLOT_BSPLINECURVE
#define CURVEPLOT_BSPLINECURVE

#include "CurveItem.hpp"

class BSplineCurve : public CurveItem
{
public:
    BSplineCurve(MH::Node *bsplineCurveNode);

    void    createPointItems();

    void    pointItemChanged();
    void    transformChanged();
    void    modelChanged();

private:
    void    createPointItems_();
    void    updateCurvePath_();
    Eigen::Array4Xd getPointItemArray_();
    QPointF         bezier_(double &t, int i, int j) const;
};

#endif
