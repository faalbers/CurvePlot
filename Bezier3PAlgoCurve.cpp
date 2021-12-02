#include "Bezier3PAlgoCurve.hpp"
#include "Eigen/Dense"

Bezier3PAlgoCurve::Bezier3PAlgoCurve()
    : CurveItem(3)
{
    controlPoints.append(std::make_shared<PointItem>(QPointF(50,500), this));
    controlPoints.append(std::make_shared<PointItem>(QPointF(300,100), this));
    controlPoints.append(std::make_shared<PointItem>(QPointF(550,500), this));
    updateCurve();
}

void Bezier3PAlgoCurve::updateCurve()
{
    // get control points
    Eigen::Matrix<double, 3, 2> pointsMatrix;
    int row = 0;
    for ( auto &controlPoint : controlPoints ) {
        pointsMatrix(row, 0) = controlPoint->pos().x()+5;
        pointsMatrix(row, 1) = controlPoint->pos().y()+5;
        row++;
    }

    // make curve algorithm matrix multiplier
    Eigen::Matrix3d curveAlgoMatrix;
    curveAlgoMatrix
    <<   1,  0,  0,
        -2,  2,  0,
         1, -2,  1;
    
    // create curve path list
    pathPoints.clear();
    Eigen::Matrix<double, 1, 3> afine;
    int subCount = 50;
    for ( int sub = 0; sub <= subCount; sub++) {
        double t = (double) sub / 50;
        afine << 1, t, pow(t,2);
        auto result = afine * curveAlgoMatrix * pointsMatrix;
        pathPoints.append(QPointF(result(0,0),result(0,1)));
    }

    update();
}
