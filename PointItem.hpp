#ifndef CURVEPLOT_POINTITEM
#define CURVEPLOT_POINTITEM

#include <QGraphicsEllipseItem>

class CurveItem;

class PointItem : public QGraphicsEllipseItem
{

public:
    PointItem(QPointF position, CurveItem *curve_, size_t index_);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent (QGraphicsSceneMouseEvent* event) {}
    void mouseMoveEvent (QGraphicsSceneMouseEvent* event);

    CurveItem   *curve;
    size_t      index;
};

#endif
