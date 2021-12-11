#include "BSplineCurve.hpp"
#include <QBrush>

#include <iostream>

BSplineCurve::BSplineCurve(MH::Node *bsplineCurveNode)
    : CurveItem(bsplineCurveNode)
{
    createPointItems_();
    updateCurvePath_();
    /*
    setControlPoints();
    auto transform = bsplineCurveNode_->getTransform();
    Eigen::Array4Xd newcPoints = transform * controlPoints.matrix();
    bool setBlue = false;
    for ( size_t index = 0; index < newcPoints.cols(); index++ ) {
        auto pItem = std::make_shared<PointItem>(QPointF(newcPoints(0,index),newcPoints(1,index)), this);
        if ( setBlue ) pItem->setBrush(QBrush(Qt::blue));
        setBlue = !setBlue;
        pointItems.append(pItem);
    }
    updateCurvePath();
    */
}

void BSplineCurve::pointItemChanged()
{
    std::cout << "BSplineCurve::pointItemChanged\n";
}

void BSplineCurve::transformChanged()
{
    // get MH and model info
    auto cpPoints = getPointItemArray_();
    auto transform = curveNode_->getTransform();

    // transform to 2D screen
    cpPoints = transform * cpPoints.matrix();

    // set pointItems from transformed cpPoints
    size_t index = 0;
    for ( auto &pointItem : pointItems_ ) {
        pointItem->setPos(cpPoints(0,index)-5,cpPoints(1,index)-5);
        index ++;
    }
    updateCurvePath_();
}

void BSplineCurve::modelChanged()
{
    std::cout << "BSplineCurve::modelChanged\n";
}

void BSplineCurve::createPointItems_()
{
    // get MH and model info
    auto cpPoints = getPointItemArray_();
    auto transform = curveNode_->getTransform();

    // transform to 2D screen
    cpPoints = transform * cpPoints.matrix();

    // create pointItems from cpPoints
    bool isTangent = false;
    for ( size_t index = 0; index < cpPoints.cols(); index++ ) {
        auto pointItem = std::make_shared<PointItem>(QPointF(cpPoints(0,index),cpPoints(1,index)), this);
        pointItems_.append(pointItem);
        if (isTangent) pointItem->setBrush(QBrush(Qt::blue));
        isTangent = !isTangent;
    }
}

void BSplineCurve::updateCurvePath_()
{
    // get recalculated path vertices and get them transformed
    auto vPoints = curveNode_->getTransformedVertices();
    pathPoints_.clear();
    for ( size_t index = 0; index < vPoints.cols(); index++ )
        pathPoints_.append(QPointF(vPoints(0, index), vPoints(1,index)));

    // repaint curve    
    update();
}

Eigen::Array4Xd BSplineCurve::getPointItemArray_()
{
    auto cpPoints = curveModel_->getPointArray("cp");
    auto cpTAngle = curveModel_->getValueArray("tangle");
    auto cpTSize = curveModel_->getValueArray("tsize");
    Eigen::Array4Xd pointItemArray(4,cpPoints.cols()*2);
    Eigen::ArrayXd cpPointTangent(4);
    pointItemArray.setZero();
    for ( size_t index = 0; index < cpPoints.cols(); index++ ) {
        pointItemArray.col(index*2) = cpPoints.col(index);
        cpPointTangent(0) = cos(cpTAngle(index));
        cpPointTangent(1) = sin(cpTAngle(index));
        cpPointTangent *= cpTSize(index);
        cpPointTangent += pointItemArray.col(index*2);
        cpPointTangent(2) = 0; cpPointTangent(3) = 1;
        pointItemArray.col((index*2)+1) = cpPointTangent;
    }
    return pointItemArray;
}
/*
void BSplineCurve::updateControlPoints()
{
    auto transform = bsplineCurveNode_->getTransform();
    Eigen::Array4Xd newcPoints = transform * controlPoints.matrix();
    size_t index = 0;
    for ( auto &pointItem : pointItems ) {
        pointItem->setPos(newcPoints(0,index)-5,newcPoints(1,index)-5);
        if ( newcPoints(2,index) > 0 ) pointItem->setBrush(QBrush(Qt::white));
        else pointItem->setBrush(QBrush(Qt::black));
        index ++;
    }
}

void BSplineCurve::updateCurvePath()
{
}

QPointF BSplineCurve::bezier_(double &t, int i, int j) const
{
    if ( j > 0 ) {
        return ((1.0-t)*bezier_(t,i,j-1) + t*bezier_(t,i-1,j-1));
    } else {
        return QPointF(pointItems[i]->pos().x()+5,pointItems[i]->pos().y()+5);
    }
}
*/