#include "ChaikinCurve.hpp"
#include "Eigen/Dense"

ChaikinCurve::ChaikinCurve()
{
    controlPoints.append(std::make_shared<PointItem>(QPointF(50,500), this));
    controlPoints.append(std::make_shared<PointItem>(QPointF(50,100), this));
    controlPoints.append(std::make_shared<PointItem>(QPointF(550,100), this));
    controlPoints.append(std::make_shared<PointItem>(QPointF(550,500), this));
    updateCurve();
}

void ChaikinCurve::updateCurve()
{
    // get control points
    Eigen::Matrix<double, 4, 3> pointsMatrix;
    int row = 0;
    for ( auto &controlPoint : controlPoints ) {
        pointsMatrix(row, 0) = controlPoint->pos().x()+5;
        pointsMatrix(row, 1) = controlPoint->pos().y()+5;
        pointsMatrix(row, 2) = 1;
        row++;
    }

    // make curve algorithm matrix multiplier
    Eigen::Matrix4d curveAlgoMatrix;
    curveAlgoMatrix
    <<   1,  0,  0,  0,
        -3,  3,  0,  0,
         3, -6,  3,  0,
        -1,  3, -3,  1;

    // create curve path list
    pathPoints.clear();
    int subCount = 50;
    for ( int sub = 0; sub <= subCount; sub++) {
        double t = (double) sub / 50;
        Eigen::Matrix<double, 1, 4> afine;
        afine << 1, t, pow(t,2), pow(t,3);
        auto result = afine * curveAlgoMatrix * pointsMatrix;
        pathPoints.append(QPointF(result(0,0),result(0,1)));
    }

    update();
}
