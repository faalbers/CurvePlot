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

    void            addToScene(QGraphicsScene *scene);
    void            removeFromScene(QGraphicsScene *scene);
    virtual void    updateControlPoints() = 0;
    virtual void    updateCurvePath() = 0;

    std::string                         name;
    size_t                              controlPointNum;
    QList<std::shared_ptr<PointItem>>   controlPoints;
    QList<QPointF>                      pathPoints;
};

#endif
