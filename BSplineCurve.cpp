#include "BSplineCurve.hpp"
#include <QBrush>

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

void BSplineCurve::pointItemChanged(size_t itemIndex, QPointF offset)
{
    auto cpPoints = getCPPoints_();
    cpPoints(0, itemIndex) += offset.x();
    cpPoints(1, itemIndex) += offset.y();
    setCPPoints_(cpPoints);
    transformChanged();
    /*
    auto cpCount = curveModel_->getPointArrayCount("cp");
    auto tCount = curveModel_->getPointArrayCount("tangent");
    auto count = cpCount + tCount;
    if ( pointItems_.size() != count )
        error_("ChaikinCurve::pointItemChanged: control points count mismatch");
    
    auto cpPoints = curveModel_->getPointArray("cp");
    auto transform = curveNode_->getTransform();
    cpPoints = transform * cpPoints.matrix();
    cpPoints(0, itemIndex) += offset.x();
    cpPoints(1, itemIndex) += offset.y();
    transform = curveNode_->getTransformInverse();
    cpPoints = transform * cpPoints.matrix();
    curveModel_->setPointArray("cp", cpPoints);
    transformChanged();
    */

    /*
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
    */
}

void BSplineCurve::transformChanged()
{
    auto cpPoints = getCPPoints_();
    size_t index = 0;
    for ( auto &pointItem : pointItems_ ) {
        pointItem->setPos(cpPoints(0,index)-5,cpPoints(1,index)-5);
        index ++;
    }
    updateCurvePath_();

    /*
    // get MH and model info
    auto cpPoints = curveModel_->getPointArray("cp");
    auto transform = curveNode_->getTransform();

    // transform to 2D screen
    cpPoints = transform * cpPoints.matrix();

    // set pointItems from transformed cpPoints
    size_t index = 0;
    for ( auto &pointItem : pointItems_ ) {
        pointItem->setPos(cpPoints(0,index)-5,cpPoints(1,index)-5);
        index ++;
    }
    */

    /*
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
    */
}

void BSplineCurve::modelChanged()
{
    //updateCurvePath_();
}

void BSplineCurve::createPointItems_()
{
    // transform to 2D screen
    auto cPoints = getCPPoints_();
    auto tCount = cPoints.cols()/2;

    // create pointItems from cpPoints
    for ( size_t index = 0; index < cPoints.cols(); index++ ) {
        auto pointItem = std::make_shared<PointItem>(QPointF(cPoints(0,index),cPoints(1,index)), this, index);
        if ( index >= tCount ) pointItem->setBrush(QBrush(Qt::blue));
        pointItems_.append(pointItem);
    }

    /*
    // get MH and model info
    auto cpPoints = getPointItemArray_();
    auto transform = curveNode_->getTransform();

    // transform to 2D screen
    cpPoints = transform * cpPoints.matrix();

    // create pointItems from cpPoints
    bool isTangent = false;
    for ( size_t index = 0; index < cpPoints.cols(); index++ ) {
        auto pointItem = std::make_shared<PointItem>(QPointF(cpPoints(0,index),cpPoints(1,index)), this, index);
        pointItems_.append(pointItem);
        if (isTangent) pointItem->setBrush(QBrush(Qt::blue));
        isTangent = !isTangent;
    }
    */
}

void BSplineCurve::updateCurvePath_()
{
    auto vertices = curveModel_->getVertices();
    /*
    // get recalculated path vertices and get them transformed
    auto vPoints = curveNode_->getTransformedVertices();
    pathPoints_.clear();
    for ( size_t index = 0; index < vPoints.cols(); index++ )
        pathPoints_.append(QPointF(vPoints(0, index), vPoints(1,index)));

    // repaint curve    
    update();
    */
}
/*
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
*/

Eigen::Array4Xd BSplineCurve::getCPPoints_() const
{
    auto cpCount = curveModel_->getPointArrayCount("cp");
    auto tCount = curveModel_->getPointArrayCount("tangent");
    auto count = cpCount + tCount;
    Eigen::Array4Xd points(4, count);
    points.leftCols(tCount) = curveModel_->getPointArray("cp");
    auto tPoints = curveModel_->getPointArray("tangent");
    for ( size_t index = 0; index < tCount; index++ ) {
        points.col(cpCount+index) = points.col(index) + tPoints.col(index);
        points(3, cpCount+index) = 1;
    }
    
    auto transform = curveNode_->getTransform();

    // transform to 2D screen
    points = transform * points.matrix();

    return points;
}

void BSplineCurve::setCPPoints_(Eigen::Array4Xd cpPoints)
{
    // transform to model transform
    auto transform = curveNode_->getTransformInverse();
    cpPoints = transform * cpPoints.matrix();
    
    // get tangent offsets
    auto count = cpPoints.cols()/2;
    for ( size_t index = 0; index < count; index++ ) {
        cpPoints.col(count+index) -= cpPoints.col(index);
        cpPoints(3, count+index) = 1;
    }

    // put arrays back
    curveModel_->setPointArray("cp", cpPoints.leftCols(count));
    curveModel_->setPointArray("tangent", cpPoints.rightCols(count));
}