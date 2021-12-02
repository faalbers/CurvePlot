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
    CurveItem(int controlPointNum_);

    void  addToScene(QGraphicsScene *scene);
    void  removeFromScene(QGraphicsScene *scene);
    void  setControlPointNum(int &pointNum);
    int   getControlPointNum() const;
    virtual void updateCurve();

    int                               controlPointNum;
    QList<std::shared_ptr<PointItem>> controlPoints;
    QList<QPointF>                    pathPoints;
};

#endif
