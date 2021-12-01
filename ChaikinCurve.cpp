#include "ChaikinCurve.hpp"

ChaikinCurve::ChaikinCurve()
{
    controlPoints.append(std::make_shared<PointItem>(QPointF(50,500), this));
    controlPoints.append(std::make_shared<PointItem>(QPointF(300,100), this));
    controlPoints.append(std::make_shared<PointItem>(QPointF(550,500), this));
    updateCurve();
}

void ChaikinCurve::updateCurve()
{
    pathPoints.clear();
    for ( auto &controlPoint : controlPoints ) pathPoints.append(controlPoint->pos()+QPointF(5,5));
    update();
}
