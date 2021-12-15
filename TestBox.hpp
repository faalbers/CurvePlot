#ifndef CURVEPLOT_TESTBOX
#define CURVEPLOT_TESTBOX

#include "CurveItem.hpp"

class TestBox : public CurveItem
{
public:
    TestBox(MH::Node *testBoxNode, MH::Node *cameraNode);

    void    pointItemChanged(size_t itemIndex, QPointF offset);
    void    transformChanged();
    void    modelChanged();

private:
    void    updateCurvePath_();
};

#endif
