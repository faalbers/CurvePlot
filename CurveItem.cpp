#include "CurveItem.hpp"
#include <QPainter>
#include <QGraphicsScene>
#include "Eigen/Dense"

CurveItem::CurveItem()
{
}

void CurveItem::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);
    for ( auto &controlPoint : controlPoints ) scene->addItem(controlPoint.get());
}

void CurveItem::updateCurve()
{
    update();
}

QRectF CurveItem::boundingRect() const
{
    return QRectF(-100, -100, 800, 800);
}

void CurveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    Eigen::Matrix<double, 4, 3> pointsMatrix;
    int row = 0;
    for ( auto &pathPoint : pathPoints ) {
        pointsMatrix(row, 0) = pathPoint.x();
        pointsMatrix(row, 1) = pathPoint.y();
        pointsMatrix(row, 2) = 1;
        row++;
    }

    Eigen::Matrix4d curveAlgoMatrix;
    curveAlgoMatrix
    <<   1,  0,  0,  0,
        -3,  3,  0,  0,
         3, -6,  3,  0,
        -1,  3, -3,  1;


    for ( int sub = 0; sub <= 50; sub++) {
        double t = (double) sub / 50;
        Eigen::Matrix<double, 1, 4> afine;
        afine << 1, t, pow(t,2), pow(t,3);
        auto result = afine * curveAlgoMatrix * pointsMatrix;
        if (sub == 0)
            path.moveTo(result(0,0), result(0,1));
        else
            path.lineTo(result(0,0), result(0,1));
    }

    painter->setPen(Qt::white);
    painter->drawPath(path);
}
