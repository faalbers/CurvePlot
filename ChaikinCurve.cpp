#include "ChaikinCurve.hpp"

ChaikinCurve::ChaikinCurve(MH::Node *chaikinCurveNode)
    : CurveItem(chaikinCurveNode)
{
    createPointItems_();
    updateCurvePath_();
}

void ChaikinCurve::pointItemChanged()
{
    // get control points and feed them transform inverted
    auto cpPoints = curveModel_->getPointArray("cp");
    size_t index = 0;
    for ( auto &pointItem : pointItems_ ) {
        cpPoints(0,index) = pointItem->pos().x()+5;
        cpPoints(1,index) = pointItem->pos().y()+5;
        index ++;
    }

    auto transform = curveNode_->getTransformInverse();
    cpPoints = transform * cpPoints.matrix();

    // update model with new cp points
    curveModel_->setPointArray("cp", cpPoints);

    updateCurvePath_();
}

void ChaikinCurve::transformChanged()
{
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
    updateCurvePath_();
}

void ChaikinCurve::modelChanged()
{
    updateCurvePath_();
}

void ChaikinCurve::createPointItems_()
{
    // get MH and model info
    auto cpPoints = curveModel_->getPointArray("cp");
    auto transform = curveNode_->getTransform();

    // transform to 2D screen
    cpPoints = transform * cpPoints.matrix();

    // create pointItems from cpPoints
    for ( size_t index = 0; index < cpPoints.cols(); index++ )
        pointItems_.append(std::make_shared<PointItem>(QPointF(cpPoints(0,index),cpPoints(1,index)), this));
}

void ChaikinCurve::updateCurvePath_()
{
    // get recalculated path vertices and get them transformed
    auto vPoints = curveNode_->getTransformedVertices();
    pathPoints_.clear();
    for ( size_t index = 0; index < vPoints.cols(); index++ )
        pathPoints_.append(QPointF(vPoints(0, index), vPoints(1,index)));

    // repaint curve    
    update();
}
