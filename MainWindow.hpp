#ifndef CURVEPLOT_MAINWINDOW
#define CURVEPLOT_MAINWINDOW

#include <QMainWindow>
#include "CurveItem.hpp"

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

private:
    Ui::MainWindow* ui_;
    QGraphicsScene* graphicsScene_;
    CurveItem*      currentCurve_;
};

#endif
