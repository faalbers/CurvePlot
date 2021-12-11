#include "CurveItem.hpp"
#include <QPainter>
#include <QGraphicsScene>

CurveItem::CurveItem(MH::Node *curveNode)
    : name_(curveNode->pathName())
    , curveNode_(curveNode)
    , curveModel_(curveNode->getModel().get())
{
}

void CurveItem::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);
    for ( auto &pointItem : pointItems_ ) scene->addItem(pointItem.get());
}

void CurveItem::removeFromScene(QGraphicsScene *scene)
{
    for ( auto &pointItem : pointItems_ ) scene->removeItem(pointItem.get());
    scene->removeItem(this);
}

const std::string &CurveItem::getName() const
{
    return name_;
}

QRectF CurveItem::boundingRect() const
{
    return QRectF(-100, -100, 800, 800);
}

void CurveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // create curve path
    QPainterPath path;
    int index = 0;
    for ( auto &pathPoint : pathPoints_ ) {
        if ( index == 0)
            path.moveTo(pathPoint);
        else
            path.lineTo(pathPoint);
        index++;
    }

    // paint curve path
    painter->setPen(Qt::white);
    painter->drawPath(path);
}
