#include "ChaikinCurve.hpp"
#include "Eigen/Dense"

ChaikinCurve::ChaikinCurve(int controlPointNum_)
    : CurveItem(controlPointNum_)
    , levels_(4)
{
    auto subAngle = M_PI / (controlPointNum-1);
    for ( int sub = 0; sub < controlPointNum; sub++ ) {
        auto angle = subAngle * sub;
        controlPoints.append(std::make_shared<PointItem>(QPointF(300-(cos(angle)*300),450-(sin(angle)*300)), this));
    }

    updateCurve();
}

void ChaikinCurve::updateCurve()
{
    pathPoints.clear();
    for ( auto &controlPoint : controlPoints )
        pathPoints.append(QPointF(controlPoint->pos().x()+5, controlPoint->pos().y()+5));
    for ( int level = 0; level < levels_; level++ ) chaikin_();
    update();
}

void ChaikinCurve::chaikin_()
{
    if ( pathPoints.size() == 0 ) return;
    QList<QPointF> newPathPoints;
    auto lastPathPoint = pathPoints[0];
    bool firstPoint = true;
    for ( auto pathPoint : pathPoints ) {
        if ( firstPoint ) {
            firstPoint = false;
            continue;
        }
        auto pathVector = pathPoint - lastPathPoint;
        newPathPoints.append(lastPathPoint + (pathVector * 0.25));
        newPathPoints.append(lastPathPoint + (pathVector * 0.75));
        lastPathPoint = pathPoint;
    }
    pathPoints = newPathPoints;
}