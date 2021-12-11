#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QGraphicsView>

#include "ChaikinCurve.hpp"
#include "BSplineCurve.hpp"

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
    connect(ui_->pointNum, SIGNAL(valueChanged(int)), this, SLOT(changeCurvePointNum(int)));
    connect(ui_->recurse, SIGNAL(valueChanged(int)), this, SLOT(changeCurveRecurse(int)));
    connect(ui_->posX, SIGNAL(valueChanged(int)), this, SLOT(changeCurvePosX(int)));
    connect(ui_->posY, SIGNAL(valueChanged(int)), this, SLOT(changeCurvePosY(int)));
    connect(ui_->rot, SIGNAL(valueChanged(int)), this, SLOT(changeCurveRot(int)));
    connect(ui_->resetTransform, SIGNAL(clicked()), this, SLOT(resetTransform()));

    // setup chaiking curve
    mh_ = std::make_shared<MH::ModelHierachy>();
    mh_->setFrameAxisY(0.0,-1.0,0.0);
    mh_->setFramePosition(300.0,300.0,0.0);
    auto chaikin = std::make_shared<MH::ChaikinCurve>(ui_->pointNum->value(),ui_->recurse->value());
    chaikinNode_ = mh_->addModel(chaikin, "Chaikin");
    auto bspline = std::make_shared<MH::BSpline>(ui_->pointNum->value());
    bsplineNode_ = mh_->addModel(bspline, "BSpline");

    changeCurveType(ui_->curveType->currentText());

}

MainWindow::~MainWindow()
{
    if ( currentCurve_ != nullptr ) delete currentCurve_;
    if ( graphicsScene_ != nullptr ) delete graphicsScene_;
}

void MainWindow::changeCurveType(const QString &curveType)
{
    // remove prior curve if needed
    if ( currentCurve_ != nullptr ) {
        currentCurve_->removeFromScene(graphicsScene_);
        delete currentCurve_;
        currentCurve_ = nullptr;
        ui_->pointNum->setEnabled(false);
        ui_->recurse->setEnabled(false);
        disableTransform();
    }

    // add new curve representation
    if ( curveType == "Chaikin") {
        ui_->pointNum->setEnabled(true);
        ui_->recurse->setEnabled(true);
        enableTransform();
        chaikinNode_->getModel()->setCount("cpnum", ui_->pointNum->value());
        currentCurve_ = new ChaikinCurve(chaikinNode_);
        currentCurve_->addToScene(graphicsScene_);
    } else if ( curveType == "BSpline") {
        ui_->pointNum->setEnabled(true);
        enableTransform();
        bsplineNode_->getModel()->setCount("cpnum", ui_->pointNum->value());
        currentCurve_ = new BSplineCurve(bsplineNode_);
        currentCurve_->addToScene(graphicsScene_);
    } else return;
}

void MainWindow::changeCurvePointNum(int pointNum)
{
    if ( ui_->pointNum->isEnabled() ) {
        changeCurveType(ui_->curveType->currentText());
    }
}

void MainWindow::changeCurveRecurse(int recurse)
{
    if ( currentCurve_ != nullptr ) {
        if ( currentCurve_->getName() == "/World/Chaikin" ) {
            chaikinNode_->getModel()->setCount("recursions", recurse);
            currentCurve_->modelChanged();
        } else if ( currentCurve_->getName() == "/World/BSpline" ) {
        }
    }
}

void MainWindow::changeCurvePosX(int posX)
{
    if ( currentCurve_ != nullptr ) {
        if ( currentCurve_->getName() == "/World/Chaikin" ) chaikinNode_->setTx(posX);
        else if ( currentCurve_->getName() == "/World/BSpline" ) bsplineNode_->setTx(posX);
        currentCurve_->transformChanged();
    }
}

void MainWindow::changeCurvePosY(int posY)
{
    if ( currentCurve_ != nullptr ) {
        if ( currentCurve_->getName() == "/World/Chaikin" ) chaikinNode_->setTy(posY);
        else if ( currentCurve_->getName() == "/World/BSpline" ) bsplineNode_->setTy(posY);
        currentCurve_->transformChanged();
    }
}

void MainWindow::changeCurveRot(int rot)
{
    auto rotPi = (M_PI / 1000) * rot;
    if ( currentCurve_ != nullptr ) {
        if ( currentCurve_->getName() == "/World/Chaikin" ) chaikinNode_->setRz(rotPi);
        else if ( currentCurve_->getName() == "/World/BSpline" ) bsplineNode_->setRz(rotPi);
        currentCurve_->transformChanged();
    }
}

void MainWindow::resetTransform()
{
    ui_->posX->setValue(0);
    ui_->posY->setValue(0);
    ui_->rot->setValue(0);
}

void MainWindow::disableTransform()
{
        ui_->pointNum->setEnabled(false);
        ui_->recurse->setEnabled(false);
        ui_->posX->setEnabled(false);
        ui_->posY->setEnabled(false);
        ui_->rot->setEnabled(false);
        ui_->resetTransform->setEnabled(false);
}

void MainWindow::enableTransform()
{
        ui_->posX->setEnabled(true);
        ui_->posY->setEnabled(true);
        ui_->rot->setEnabled(true);
        ui_->resetTransform->setEnabled(true);
}
