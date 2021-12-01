#include "CurveItem.hpp"
#include <QPainter>
#include <QGraphicsScene>

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
    // create curve path
    QPainterPath path;
    int index = 0;
    for ( auto &pathPoint : pathPoints ) {
        if ( index == 0)
            path.moveTo(pathPoint);
        else
            path.lineTo(pathPoint);
        index++;
    }

    // paint curve path
    painter->setPen(Qt::white);
    painter->drawPath(path);
}
