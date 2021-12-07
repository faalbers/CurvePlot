#include "PointItem.hpp"
#include "CurveItem.hpp"
#include <QApplication>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

PointItem::PointItem(QPointF position, CurveItem *curve_)
    : curve(curve_)
{
    setBrush(QBrush(Qt::yellow));
    setRect(0, 0, 10, 10);
    setPos(position-QPointF(5,5));
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

void PointItem::mouseMoveEvent (QGraphicsSceneMouseEvent* event)
{
    setPos(event->scenePos()-QPointF(5, 5));
    curve->updateCurvePath();
}
