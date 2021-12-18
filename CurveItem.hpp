#ifndef CURVEPLOT_CURVEITEM
#define CURVEPLOT_CURVEITEM

#include <QGraphicsItem>
#include <memory>
#include "ModelHierarchy.hpp"
#include "PointItem.hpp"

#define CURVEPLOT_SCENE_WIDTH 800
#define CURVEPLOT_SCENE_HEIGHT 800

class CurveItem : public QGraphicsItem
{
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    CurveItem(MH::Node *curveNode, MH::Node *cameraNode);

    void                addToScene(QGraphicsScene *scene);
    void                removeFromScene(QGraphicsScene *scene);
    const std::string   &getName() const;

    virtual void        pointItemChanged(size_t itemIndex, QPointF offset) = 0;
    virtual void        transformChanged() = 0;
    virtual void        modelChanged() = 0;

protected:
    void                error_(std::string message) const;

    std::string                         name_;
    MH::Node                            *curveNode_;
    MH::Model                           *curveModel_;
    MH::Node                            *cameraNode_;
    MH::Model                           *cameraModel_;
    QList<std::shared_ptr<PointItem>>   pointItems_;
    QList<QPointF>                      pathPoints_;
};

#endif
