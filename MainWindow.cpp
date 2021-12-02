#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QGraphicsView>
#include "BernsteinCurve.hpp"

#include <iostream>

MainWindow::MainWindow()
    : ui_(new Ui::MainWindow)
    , graphicsScene_(nullptr)
    , currentCurve_(nullptr)
{
    ui_->setupUi(this);

    graphicsScene_ = new QGraphicsScene(0, 0, 600, 600);
    graphicsScene_->setBackgroundBrush(Qt::gray);
    ui_->curveView->setScene(graphicsScene_);

    connect(ui_->curveType, SIGNAL(currentTextChanged(const QString &)), this, SLOT(changeCurveType(const QString &)));

    changeCurveType(ui_->curveType->currentText());
    //auto curve = new BernsteinCurve;
    //curve->addToScene(gScene);
    //curve->removeFromScene(gScene);

}

MainWindow::~MainWindow()
{
    if ( currentCurve_ != nullptr ) delete currentCurve_;
    if ( graphicsScene_ != nullptr ) delete graphicsScene_;
}

void MainWindow::changeCurveType(const QString &curveType)
{
    if ( currentCurve_ != nullptr ) {
        currentCurve_->removeFromScene(graphicsScene_);
        delete currentCurve_;
        currentCurve_ = nullptr;
    }
    if ( curveType == "Bernstein" ) {
        currentCurve_ = new BernsteinCurve;
        ui_->pointNum->setValue(currentCurve_->getPointsNum());
        ui_->pointNum->setEnabled(false);
        currentCurve_->addToScene(graphicsScene_);
    }
}