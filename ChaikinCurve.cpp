#include "ChaikinCurve.hpp"
#include "Eigen/Dense"

#include <iostream>

ChaikinCurve::ChaikinCurve(MH::Node *chaikinCurveNode)
    : CurveItem(chaikinCurveNode->getModel()->getCount("cpnum"))
    , chaikinCurveNode_(chaikinCurveNode)
    , chaikinCurveModel_(chaikinCurveNode->getModel().get())
{
    auto tcPoints = chaikinCurveModel_->getPointArray("cp");
    auto transform = chaikinCurveNode_->getTransform();
    tcPoints = transform * tcPoints.matrix();
    for ( size_t index = 0; index < tcPoints.rows(); index++ )
        controlPoints.append(std::make_shared<PointItem>(QPointF(tcPoints(0,index),tcPoints(1,index)), this));
    updateCurvePath();
}

void ChaikinCurve::updateControlPoints()
{
    auto cPoints = chaikinCurveModel_->getPointArray("cp");
    auto transform = chaikinCurveNode_->getTransform();
    cPoints = transform * cPoints.matrix();
    size_t index = 0;
    for ( auto &controlPoint : controlPoints ) {
        controlPoint->setPos(cPoints(0,index)-5,cPoints(1,index)-5);
        index ++;
    }
    updateCurvePath();
}

void ChaikinCurve::updateCurvePath()
{
    // get control points and feed them transforn inverted
    auto cPoints = chaikinCurveModel_->getPointArray("cp");
    size_t index = 0;
    for ( auto &controlPoint : controlPoints ) {
        cPoints(0,index) = controlPoint->pos().x()+5;
        cPoints(1,index) = controlPoint->pos().y()+5;
        index ++;
    }
    auto transform = chaikinCurveNode_->getTransformInverse();
    cPoints = transform * cPoints.matrix();
    chaikinCurveModel_->setPointArray("cp", cPoints);

    // get recalculated path vertices and get them transformed
    auto vPoints = chaikinCurveNode_->getTransformedVertices();
    pathPoints.clear();
    for ( size_t index = 0; index < vPoints.cols(); index++ )
        pathPoints.append(QPointF(vPoints(0, index), vPoints(1,index)));
    
    update();
}
