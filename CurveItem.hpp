#ifndef CURVEPLOT_CURVEITEM
#define CURVEPLOT_CURVEITEM

#include <QGraphicsItem>
#include <memory>
#include "ModelHierarchy.hpp"
#include "PointItem.hpp"

class CurveItem : public QGraphicsItem
{
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    CurveItem(MH::Node *curveNode);

    void                addToScene(QGraphicsScene *scene);
    void                removeFromScene(QGraphicsScene *scene);
    const std::string   &getName() const;

    virtual void        pointItemChanged() = 0;
    virtual void        transformChanged() = 0;
    virtual void        modelChanged() = 0;

protected:
    std::string                         name_;
    MH::Node                            *curveNode_;
    MH::Model                           *curveModel_;
    QList<std::shared_ptr<PointItem>>   pointItems_;
    QList<QPointF>                      pathPoints_;
};

#endif
