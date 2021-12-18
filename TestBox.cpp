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

