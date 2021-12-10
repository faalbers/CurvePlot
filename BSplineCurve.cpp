#include "BSplineCurve.hpp"
#include "Eigen/Dense"

BSplineCurve::BSplineCurve(MH::Node *bsplineCurveNode)
    : CurveItem(bsplineCurveNode->getModel()->getCount("cpnum"))
{
    /*
    auto subAngle = M_PI / (controlPointNum-1);
    for ( int sub = 0; sub < controlPointNum; sub++ ) {
        auto angle = subAngle * sub;
        controlPoints.append(std::make_shared<PointItem>(QPointF(300-(cos(angle)*300),450-(sin(angle)*300)), this));
    }

    updateCurve();
    */
}

void BSplineCurve::updateCurve()
{
    /*
    pathPoints.clear();
    int subCount = 50;
    for ( int sub = 0; sub <= subCount; sub++) {
        double t = (double) sub / 50;
        pathPoints.append(bezier_(t,controlPointNum-1,controlPointNum-1));
    }
    update();
    */
}

QPointF BSplineCurve::bezier_(double &t, int i, int j) const
{
    if ( j > 0 ) {
        return ((1.0-t)*bezier_(t,i,j-1) + t*bezier_(t,i-1,j-1));
    } else {
        return QPointF(controlPoints[i]->pos().x()+5,controlPoints[i]->pos().y()+5);
    }
}