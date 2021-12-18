#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QGraphicsView>

#include "TestBox.hpp"
#include "ChaikinCurve.hpp"
#include "BSplineCurve.hpp"

MainWindow::MainWindow()
    : ui_(new Ui::MainWindow)
    , graphicsScene_(nullptr)
    , currentCurve_(nullptr)
{
    ui_->setupUi(this);

    graphicsScene_ = new QGraphicsScene(0, 0, CURVEPLOT_SCENE_WIDTH, CURVEPLOT_SCENE_HEIGHT);
    graphicsScene_->setBackgroundBrush(Qt::gray);
    ui_->curveView->setScene(graphicsScene_);

    connect(ui_->curveType, SIGNAL(currentTextChanged(const QString &)), this, SLOT(changeCurveType(const QString &)));
    connect(ui_->pointNum, SIGNAL(valueChanged(int)), this, SLOT(changeCurvePointNum(int)));
    connect(ui_->subdiv, SIGNAL(valueChanged(int)), this, SLOT(changeCurveSubdiv(int)));

    connect(ui_->tx, SIGNAL(valueChanged(int)), this, SLOT(changeCurvePosX(int)));
    connect(ui_->ty, SIGNAL(valueChanged(int)), this, SLOT(changeCurvePosY(int)));
    connect(ui_->tz, SIGNAL(valueChanged(int)), this, SLOT(changeCurvePosZ(int)));
    connect(ui_->rx, SIGNAL(valueChanged(int)), this, SLOT(changeCurveRotX(int)));
    connect(ui_->ry, SIGNAL(valueChanged(int)), this, SLOT(changeCurveRotY(int)));
    connect(ui_->rz, SIGNAL(valueChanged(int)), this, SLOT(changeCurveRotZ(int)));

    connect(ui_->resetTransform, SIGNAL(clicked()), this, SLOT(resetTransform()));

    // setup chaiking curve
    mh_ = std::make_shared<MH::ModelHierachy>();

    parentNode_ = mh_->addParent("Parent");

    auto testBox = std::make_shared<MH::TestBox>();
    testBoxNode_ = mh_->addModel(testBox, "TestBox", parentNode_);

    auto chaikin = std::make_shared<MH::ChaikinCurve>(ui_->pointNum->value(),ui_->subdiv->value());
    chaikinNode_ = mh_->addModel(chaikin, "Chaikin", parentNode_);

    auto bspline = std::make_shared<MH::BSpline>(ui_->pointNum->value(),ui_->subdiv->value());
    bsplineNode_ = mh_->addModel(bspline, "BSpline", parentNode_);

    double fov = M_PI/5.0;
    double near = -(1.0/sin(fov/2.0))*cos(fov/2.0)*CURVEPLOT_SCENE_HEIGHT/2.0;
    double far = near - (double) CURVEPLOT_SCENE_HEIGHT;
    double camZ = ((double) CURVEPLOT_SCENE_HEIGHT / 2.0) - near;
    auto camera = std::make_shared<MH::PinholeCamera>(near, far, fov,
        CURVEPLOT_SCENE_WIDTH, -CURVEPLOT_SCENE_HEIGHT);
    cameraNode_ = mh_->addModel(camera, "Camera");
    cameraNode_->setTz(camZ);

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
        ui_->subdiv->setEnabled(false);
        disableTransform();
    }

    // add new curve representation
    if ( curveType == "TestBox") {
        enableTransform();
        currentCurve_ = new TestBox(testBoxNode_,cameraNode_);
        currentCurve_->addToScene(graphicsScene_);
    } else if ( curveType == "Chaikin") {
        ui_->pointNum->setEnabled(true);
        ui_->subdiv->setEnabled(true);
        enableTransform();
        chaikinNode_->getModel()->setCount("cpnum", ui_->pointNum->value());
        currentCurve_ = new ChaikinCurve(chaikinNode_,cameraNode_);
        currentCurve_->addToScene(graphicsScene_);
    } else if ( curveType == "BSpline") {
        ui_->pointNum->setEnabled(true);
        ui_->subdiv->setEnabled(true);
        enableTransform();
        bsplineNode_->getModel()->setCount("cpnum", ui_->pointNum->value());
        currentCurve_ = new BSplineCurve(bsplineNode_,cameraNode_);
        currentCurve_->addToScene(graphicsScene_);
    } else return;
}

void MainWindow::changeCurvePointNum(int pointNum)
{
    if ( ui_->pointNum->isEnabled() ) {
        changeCurveType(ui_->curveType->currentText());
    }
}

void MainWindow::changeCurveSubdiv(int subdiv)
{
    chaikinNode_->getModel()->setCount("subdiv", subdiv);
    bsplineNode_->getModel()->setCount("subdiv", subdiv);
    if ( currentCurve_ != nullptr ) currentCurve_->modelChanged();
}

void MainWindow::changeCurvePosX(int pos)
{
    auto moveScene = (double) pos * ((double) 300/1000);
    chaikinNode_->setTx(moveScene);
    bsplineNode_->setTx(moveScene);
    testBoxNode_->setTy(moveScene);
    if ( currentCurve_ != nullptr ) currentCurve_->transformChanged();
}

void MainWindow::changeCurvePosY(int pos)
{
    auto moveScene = (double) pos * ((double) 300/1000);
    chaikinNode_->setTy(moveScene);
    bsplineNode_->setTy(moveScene);
    testBoxNode_->setTy(moveScene);
    if ( currentCurve_ != nullptr ) currentCurve_->transformChanged();
}

void MainWindow::changeCurvePosZ(int pos)
{
    auto moveScene = (double) pos * ((double) 300/1000);
    chaikinNode_->setTz(moveScene);
    bsplineNode_->setTz(moveScene);
    testBoxNode_->setTz(moveScene);
    if ( currentCurve_ != nullptr ) currentCurve_->transformChanged();
}

void MainWindow::changeCurveRotX(int rot)
{
    auto rotPi = (M_PI / 1000) * rot;
    parentNode_->setRx(rotPi);
    if ( currentCurve_ != nullptr ) currentCurve_->transformChanged();
}

void MainWindow::changeCurveRotY(int rot)
{
    auto rotPi = (M_PI / 1000) * rot;
    parentNode_->setRy(rotPi);
    if ( currentCurve_ != nullptr ) currentCurve_->transformChanged();
}

void MainWindow::changeCurveRotZ(int rot)
{
    auto rotPi = (M_PI / 1000) * rot;
    parentNode_->setRz(rotPi);
    if ( currentCurve_ != nullptr ) currentCurve_->transformChanged();
}

void MainWindow::resetTransform()
{
    ui_->tx->setValue(0);
    ui_->ty->setValue(0);
    ui_->tz->setValue(0);
    ui_->rx->setValue(0);
    ui_->ry->setValue(0);
    ui_->rz->setValue(0);
}

void MainWindow::disableTransform()
{
        ui_->pointNum->setEnabled(false);
        ui_->subdiv->setEnabled(false);
        ui_->tx->setEnabled(false);
        ui_->ty->setEnabled(false);
        ui_->tz->setEnabled(false);
        ui_->rx->setEnabled(false);
        ui_->ry->setEnabled(false);
        ui_->rz->setEnabled(false);
        ui_->resetTransform->setEnabled(false);
}

void MainWindow::enableTransform()
{
        ui_->tx->setEnabled(true);
        ui_->ty->setEnabled(true);
        ui_->tz->setEnabled(true);
        ui_->rx->setEnabled(true);
        ui_->ry->setEnabled(true);
        ui_->rz->setEnabled(true);
        ui_->resetTransform->setEnabled(true);
}
