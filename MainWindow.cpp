#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QGraphicsView>
#include "ChaikinCurve.hpp"

MainWindow::MainWindow()
    : ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    auto gScene = new QGraphicsScene(0, 0, 600, 600);
    gScene->setBackgroundBrush(Qt::gray);

    auto curve = new ChaikinCurve;
    curve->addToScene(gScene);

    ui_->curveView->setScene(gScene);
}

