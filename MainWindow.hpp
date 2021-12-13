#ifndef CURVEPLOT_MAINWINDOW
#define CURVEPLOT_MAINWINDOW

#include <QMainWindow>
#include "CurveItem.hpp"
#include "ModelHierarchy.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void changeCurveType(const QString &curveType);
    void changeCurvePointNum(int pointNum);
    void changeCurveSubdiv(int recurse);
    void changeCurvePosX(int pos);
    void changeCurvePosY(int pos);
    void changeCurvePosZ(int pos);
    void changeCurveRotX(int rot);
    void changeCurveRotY(int rot);
    void changeCurveRotZ(int rot);

    void enableTransform();
    void disableTransform();
    void resetTransform();

private:    
    Ui::MainWindow* ui_;
    QGraphicsScene* graphicsScene_;
    CurveItem*      currentCurve_;
    std::shared_ptr<MH::ModelHierachy> mh_;
    MH::Node        *parentNode_;
    MH::Node        *chaikinNode_;
    MH::Node        *bsplineNode_;
};

#endif
