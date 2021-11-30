#include "PointItem.hpp"
#include <QApplication>
#include <QBrush>
#include <iostream>
#include <QGraphicsSceneMouseEvent>

PointItem::PointItem(qreal x, qreal y, CurveItem *curve_)
    : curve(curve_)
{
    setBrush(QBrush(Qt::yellow));
    setRect(0, 0, 10, 10);
    setPos(x, y);
    setAcceptHoverEvents(true);
}

void PointItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QApplication::setOverrideCursor(Qt::CrossCursor);
}

void PointItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QApplication::restoreOverrideCursor();
}

void PointItem::mousePressEvent (QGraphicsSceneMouseEvent* event)
{
}

void PointItem::mouseMoveEvent (QGraphicsSceneMouseEvent* event)
{
    setPos(event->scenePos().x()-5, event->scenePos().y()-5);
    curve->end = event->scenePos();
    curve->update();
}

void PointItem::mouseReleaseEvent (QGraphicsSceneMouseEvent* event)
{
    curve->update();
}
