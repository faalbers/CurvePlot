#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QGraphicsView>
//#include "CurveView.hpp"
#include "CurveItem.hpp"
#include "PointItem.hpp"

MainWindow::MainWindow()
    : ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    //auto curveView = new CurveView;
    //ui_->viewBox->addWidget(curveView);

    auto gScene = new QGraphicsScene(0, 0, 500, 500);
    gScene->setBackgroundBrush(Qt::gray);

    auto curve = new CurveItem;
    gScene->addItem(curve);

    auto point = new PointItem(250, 250, curve);
    gScene->addItem(point);

    ui_->curveView->setScene(gScene);
/*
    QGraphicsView(ui_->)
    
    auto gScene = new QGraphicsScene(0, 0, 500, 500);

    gScene->setBackgroundBrush(Qt::gray);


    auto painter = new QPainter(ui_->curveView);
    //painter->setPen(Qt::white);
    //painter->drawLine(0, 0, 100, 100);
    //ui_->curveView->update();

    auto point = new PointItem(250, 250);
    gScene->addItem(point);

*/
}

