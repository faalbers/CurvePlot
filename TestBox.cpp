#include "TestBox.hpp"

TestBox::TestBox(MH::Node *testBoxNode, MH::Node *cameraNode)
    : CurveItem(testBoxNode, cameraNode)
{
    updateCurvePath_();
}

void TestBox::pointItemChanged(size_t itemIndex, QPointF offset)
{
}

void TestBox::transformChanged()
{
    updateCurvePath_();
}

void TestBox::modelChanged()
{
    transformChanged();
}

void TestBox::updateCurvePath_()
{
    //auto vertices = cameraMatrix_ * curveNode_->getTransformedVertices().matrix();
    auto vertices = curveNode_->getTransformedVertices();

    pathPoints_.clear();
    for ( size_t index = 0; index < vertices.cols(); index++ )
        pathPoints_.append(QPointF(vertices(0, index), vertices(1,index)));

    update();
}

