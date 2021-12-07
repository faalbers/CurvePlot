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
    updateCurve();
}

void ChaikinCurve::updateCurve()
{
    auto tcPoints = chaikinCurveModel_->getPointArray("cp");
    auto transform = chaikinCurveNode_->getTransformInverse();
    size_t index = 0;
    for ( auto &controlPoint : controlPoints ) {
        tcPoints(index,0) = controlPoint->pos().x()+5;
        tcPoints(index,1) = controlPoint->pos().y()+5;
        index ++;
    }
    tcPoints *= transform;

    chaikinCurveModel_->setPointArray("cp", tcPoints);
    auto vPoints = chaikinCurveNode_->getTransformedVertices();
    pathPoints.clear();
    for ( size_t index = 0; index < vPoints.rows(); index++ )
        pathPoints.append(QPointF(vPoints(index,0), vPoints(index,1)));
    
    update();
}
