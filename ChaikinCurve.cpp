#include "ChaikinCurve.hpp"

#include <iostream>

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
    setCPPoint_(itemIndex, cpPoints.col(itemIndex));
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
    //auto vertices = curveNode_->getTransformedVertices();
    Eigen::Array4Xd vertices =
        cameraModel_->getMatrix("project") *
        curveNode_->getTransformTo(cameraNode_) *
        curveModel_->getPointArray("vtx").matrix();
    for ( auto vertex : vertices.colwise() ) vertex /= vertex(3);

    Eigen::Matrix4d screenMM = MH::ModelHierachy::screenTransform(
        CURVEPLOT_SCENE_WIDTH, -CURVEPLOT_SCENE_HEIGHT);
    vertices = screenMM * vertices.matrix();

    pathPoints_.clear();
    for ( size_t index = 0; index < vertices.cols(); index++ )
        pathPoints_.append(QPointF(vertices(0, index), vertices(1,index)));

    update();
}

Eigen::Array4Xd ChaikinCurve::getCPPoints_() const
{
    /*
    Eigen::Array4Xd points =
        cameraModel_->getMatrix("project") *
        curveNode_->getTransformTo(cameraNode_) *
        curveModel_->getPointArray("cp").matrix();
    for ( auto point : points.colwise() ) point /= point(3);
    Eigen::Matrix4d screenMM = MH::ModelHierachy::screenTransform(
        CURVEPLOT_SCENE_WIDTH, -CURVEPLOT_SCENE_HEIGHT);
    points = screenMM * points.matrix();
    */
    Eigen::Array4Xd points = MH::ModelHierachy::screenProject(curveNode_, cameraNode_, "cp");
    return points;
}

void ChaikinCurve::setCPPoint_(size_t index, Eigen::Vector4d cpPoint)
{
    Eigen::Vector4d point = curveModel_->getPointFromArray("cp",index);
    Eigen::Matrix4d transform =
        cameraModel_->getMatrix("project") * 
        curveNode_->getTransformTo(cameraNode_);
    point = transform * point;

    Eigen::Matrix4d screenT = MH::ModelHierachy::screenTransform(
        CURVEPLOT_SCENE_WIDTH, -CURVEPLOT_SCENE_HEIGHT);
    cpPoint = screenT.inverse() * cpPoint.matrix();
    cpPoint *= point(3);
    cpPoint = transform.inverse() * cpPoint;
    cpPoint(3) = 1.0;

    // put cp back
    curveModel_->setPointInArray("cp", index, cpPoint);
}
