#include "ChaikinCurve.hpp"
#include "Eigen/Dense"

ChaikinCurve::ChaikinCurve(MH::Node *chaikinCurveNode)
    : CurveItem(chaikinCurveNode->getModel()->getCount("cpnum"))
    , chaikinCurveNode_(chaikinCurveNode)
    , chaikinCurveModel_(chaikinCurveNode->getModel().get())
{
    auto tcPoints = chaikinCurveModel_->getPointArray("cp");
    auto transform = chaikinCurveNode_->getTransform();
    tcPoints *= transform;
    for ( size_t index = 0; index < tcPoints.rows(); index++ )
        controlPoints.append(std::make_shared<PointItem>(QPointF(tcPoints(index,0),tcPoints(index,1)), this));
    updateCurvePath();
}

void ChaikinCurve::updateControlPoints()
{
    auto cPoints = chaikinCurveModel_->getPointArray("cp");
    auto transform = chaikinCurveNode_->getTransform();
    cPoints *= transform;
    size_t index = 0;
    for ( auto &controlPoint : controlPoints ) {
        controlPoint->setPos(cPoints(index,0)-5,cPoints(index,1)-5);
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
        cPoints(index,0) = controlPoint->pos().x()+5;
        cPoints(index,1) = controlPoint->pos().y()+5;
        index ++;
    }
    auto transform = chaikinCurveNode_->getTransformInverse();
    cPoints *= transform;
    chaikinCurveModel_->setPointArray("cp", cPoints);

    // get recalculated path vertices and get them transformed
    auto vPoints = chaikinCurveNode_->getTransformedVertices();
    pathPoints.clear();
    for ( size_t index = 0; index < vPoints.rows(); index++ )
        pathPoints.append(QPointF(vPoints(index,0), vPoints(index,1)));
    
    update();
}
