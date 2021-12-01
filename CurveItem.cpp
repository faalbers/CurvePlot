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
    QPainterPath path;
    bool firstPoint = true;
    for ( auto &pathPoint : pathPoints ) {
        if (firstPoint) {
            path.moveTo(pathPoint);
            firstPoint = false;
        } else path.lineTo(pathPoint);
    }
    painter->setPen(Qt::white);
    painter->drawPath(path);
}
