#ifndef CURVEPLOT_CURVEITEM
#define CURVEPLOT_CURVEITEM

#include <QGraphicsItem>

class CurveItem : public QGraphicsItem
{
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    CurveItem();

    QPointF start, end;
};

#endif
