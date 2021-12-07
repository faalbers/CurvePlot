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
    void changeCurveRecurse(int recurse);
    void changeCurvePosX(int posX);
    void changeCurvePosY(int posX);
    void changeCurveRot(int rot);

private:
    Ui::MainWindow* ui_;
    QGraphicsScene* graphicsScene_;
    CurveItem*      currentCurve_;
    std::shared_ptr<MH::ModelHierachy> mh_;
    MH::Node        *chaikinNode_;
};

#endif
