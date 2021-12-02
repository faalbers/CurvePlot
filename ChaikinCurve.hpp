#ifndef CURVEPLOT_CHAIKINCURVE
#define CURVEPLOT_CHAIKINCURVE

#include "CurveItem.hpp"

class ChaikinCurve : public CurveItem
{
public:
    ChaikinCurve(int controlPointNum_);

    void updateCurve();

private:
    void chaikin_();

    int levels_;
};

#endif
