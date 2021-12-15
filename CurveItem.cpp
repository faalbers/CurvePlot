#include "CurveItem.hpp"
#include <QPainter>
#include <QGraphicsScene>
#include <iostream>

CurveItem::CurveItem(MH::Node *curveNode, MH::Node *cameraNode)
    : name_(curveNode->pathName())
    , curveNode_(curveNode)
    , curveModel_(curveNode->getModel().get())
    , cameraNode_(cameraNode)
    , cameraModel_(cameraNode->getModel().get())
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
    return QRectF(0, 0, 1000, 800);
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

void CurveItem::error_(std::string message) const
{
    std::cout << "CurveItem:" << std::endl;
    std::cout << "-> " << message << std::endl;
    std::cout << "exit application ..." << std::endl;
    exit(1);
}