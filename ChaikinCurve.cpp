#include "ChaikinCurve.hpp"

ChaikinCurve::ChaikinCurve(MH::Node *chaikinCurveNode, MH::Node *cameraNode)
    : CurveItem(chaikinCurveNode, cameraNode)
{
    createPointItems_();
    updateCurvePath_();
}

void ChaikinCurve::pointItemChanged(size_t itemIndex, QPointF offset)
{
    auto cpPoints = getCPPoints_();
    cpPoints(0, itemIndex) += offset.x();
    cpPoints(1, itemIndex) += offset.y();
    setCPPoints_(cpPoints);
    transformChanged();
}

void ChaikinCurve::transformChanged()
{
    auto cpPoints = getCPPoints_();
    size_t index = 0;
    for ( auto &pointItem : pointItems_ ) {
        pointItem->setPos(cpPoints(0,index)-5,cpPoints(1,index)-5);
        index ++;
    }
    updateCurvePath_();
}

void ChaikinCurve::modelChanged()
{
    transformChanged();
}

void ChaikinCurve::createPointItems_()
{
    // get MH and model info
    auto cpPoints = getCPPoints_();

    // create pointItems from cpPoints
    for ( size_t index = 0; index < cpPoints.cols(); index++ ) {
        pointItems_.append(std::make_shared<PointItem>(QPointF(cpPoints(0,index),cpPoints(1,index)), this, index));
    }
}

void ChaikinCurve::updateCurvePath_()
{
    //auto vertices = cameraMatrix_ * curveNode_->getTransformedVertices().matrix();
    auto vertices = curveNode_->getTransformedVertices();

    pathPoints_.clear();
    for ( size_t index = 0; index < vertices.cols(); index++ )
        pathPoints_.append(QPointF(vertices(0, index), vertices(1,index)));

    update();
}

Eigen::Array4Xd ChaikinCurve::getCPPoints_() const
{
    // get MH and model info
    auto points = curveModel_->getPointArray("cp");
    auto transform = curveNode_->getTransform();

    // transform to 2D screen
    points = transform * points.matrix();

    return points;
}

void ChaikinCurve::setCPPoints_(Eigen::Array4Xd cpPoints)
{
    // transform to model transform
    auto transform = curveNode_->getTransformInverse();
    cpPoints = transform * cpPoints.matrix();
    
    // put array back
    curveModel_->setPointArray("cp", cpPoints);
}
