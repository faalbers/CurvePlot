#include "ChaikinCurve.hpp"

ChaikinCurve::ChaikinCurve(MH::Node *chaikinCurveNode, MH::Node *cameraNode)
    : CurveItem(chaikinCurveNode, cameraNode)
{
    createPointItems_();
    updateCurvePath_();
}

void ChaikinCurve::pointItemChanged(size_t itemIndex, QPointF offset)
{
    auto cpPoints = MH::ModelHierachy::pointsToScreen(curveNode_, cameraNode_, "cp");
    cpPoints(0, itemIndex) += offset.x();
    cpPoints(1, itemIndex) += offset.y();
    MH::ModelHierachy::screenToPoint(curveNode_, cameraNode_, "cp", itemIndex, cpPoints.col(itemIndex));
    transformChanged();
}

void ChaikinCurve::transformChanged()
{
    auto cpPoints = MH::ModelHierachy::pointsToScreen(curveNode_, cameraNode_, "cp");
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
    auto cpPoints = MH::ModelHierachy::pointsToScreen(curveNode_, cameraNode_, "cp");

    // create pointItems from cpPoints
    for ( size_t index = 0; index < cpPoints.cols(); index++ ) {
        pointItems_.append(std::make_shared<PointItem>(QPointF(cpPoints(0,index),cpPoints(1,index)), this, index));
    }
}

void ChaikinCurve::updateCurvePath_()
{
    Eigen::Array4Xd vertices = MH::ModelHierachy::pointsToScreen(curveNode_, cameraNode_, "vtx");

    pathPoints_.clear();
    for ( size_t index = 0; index < vertices.cols(); index++ )
        pathPoints_.append(QPointF(vertices(0, index), vertices(1,index)));

    update();
}
