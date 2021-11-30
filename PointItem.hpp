#ifndef CURVEPLOT_POINTITEM
#define CURVEPLOT_POINTITEM

#include <QGraphicsEllipseItem>
#include "CurveItem.hpp"

class PointItem : public QGraphicsEllipseItem
{

public:
    PointItem(qreal x, qreal y, CurveItem *curve_);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent (QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent (QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent* event);

    CurveItem *curve;
};

#endif
