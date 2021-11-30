#include "CurveItem.hpp"
#include <QPainter>

CurveItem::CurveItem()
{
    start.setX(0);
    start.setY(0);
    end.setX(100);
    end.setY(100);
}

QRectF CurveItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-100, -100, 700, 700);
}

void CurveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->drawLine(start, end);
}
