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
    // get control points and feed them transform inverted
    Eigen::Array4Xd piPoints(4,pointItems_.size());
    piPoints.row(2).setZero();
    piPoints.row(3).setOnes();
    size_t index = 0;
    for ( auto &pointItem : pointItems_ ) {
        piPoints(0,index) = pointItem->pos().x()+5;
        piPoints(1,index) = pointItem->pos().y()+5;
        index ++;
    }

    auto transform = curveNode_->getTransformInverse();
    piPoints = transform * piPoints.matrix();

    // get cp points from model
    auto cpPoints = curveModel_->getPointArray("cp");
    auto tangleValues = curveModel_->getValueArray("tangle");
    auto tsizeValues = curveModel_->getValueArray("tsize");
    size_t picpIndex, pitIndex;
    Eigen::Vector3d xVector; xVector.setZero(); xVector(0) = 1;
    Eigen::Vector3d tVector;
    for ( size_t cpIndex = 0; cpIndex < cpPoints.cols(); cpIndex++ ) {
        picpIndex = cpIndex*2;
        pitIndex = picpIndex+1;
        cpPoints.col(cpIndex) = piPoints.col(picpIndex);
        auto tVectorD = piPoints.col(pitIndex)-piPoints.col(picpIndex);
        tVector(0) = tVectorD(0); tVector(1) = tVectorD(1); tVector(2) = tVectorD(2); 
        tsizeValues(cpIndex) = tVector.norm();
        tVector.normalize();
        auto cross =xVector.cross(tVector)(2);
        auto sign = (double)(cross > 0) - (double)(cross < 0);
        tangleValues(cpIndex) = acos(tVector.dot(xVector))*sign;
    }
    curveModel_->setPointArray("cp", cpPoints);
    curveModel_->setValueArray("tangle", tangleValues);
    curveModel_->setValueArray("tsize", tsizeValues);

    updateCurvePath_();
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
