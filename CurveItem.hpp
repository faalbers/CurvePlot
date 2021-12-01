#ifndef CURVEPLOT_CURVEITEM
#define CURVEPLOT_CURVEITEM

#include <QGraphicsItem>
#include <memory>
#include "PointItem.hpp"

class CurveItem : public QGraphicsItem
{
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    CurveItem();

    void addToScene(QGraphicsScene *scene);
    virtual void updateCurve();

    QList<std::shared_ptr<PointItem>> controlPoints;
    QList<QPointF>                    pathPoints;
};

#endif
