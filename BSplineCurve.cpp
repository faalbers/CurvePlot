#include "BSplineCurve.hpp"
#include <QBrush>

BSplineCurve::BSplineCurve(MH::Node *bsplineCurveNode, MH::Node *cameraNode)
    : CurveItem(bsplineCurveNode, cameraNode)
{
    createPointItems_();
    updateCurvePath_();
}

void BSplineCurve::pointItemChanged(size_t itemIndex, QPointF offset)
{
    auto cpPoints = getCPPoints_();
    cpPoints(0, itemIndex) += offset.x();
    cpPoints(1, itemIndex) += offset.y();
    setCPPoints_(cpPoints);
    transformChanged();
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
}

void BSplineCurve::modelChanged()
{
    transformChanged();
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
}

void BSplineCurve::updateCurvePath_()
{
    auto vertices = curveModel_->getPointArray("vtx");
    MH::ModelHierachy::pointsToScreen(curveNode_, cameraNode_, vertices);
    
    pathPoints_.clear();
    for ( size_t index = 0; index < vertices.cols(); index++ )
        pathPoints_.append(QPointF(vertices(0, index), vertices(1,index)));

    update();
}

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

    MH::ModelHierachy::pointsToScreen(curveNode_, cameraNode_, points);

    return points;
}

void BSplineCurve::setCPPoints_(Eigen::Array4Xd cpPoints)
{

    MH::ModelHierachy::screenToPoints(curveNode_, cameraNode_, cpPoints);
    
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