#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QGraphicsView>

#include "ChaikinCurve.hpp"

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

    // setup chaiking curve
    mh_ = std::make_shared<MH::ModelHierachy>();
    mh_->setFrameAxisY(0.0,-1.0,0.0);
    mh_->setFramePosition(300.0,300.0,0.0);
    auto chaikin = std::make_shared<MH::ChaikinCurve>(ui_->pointNum->value(),ui_->recurse->value());
    chaikinNode_ = mh_->addModel(chaikin, "Chaikin");

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
    }

    // add new curve
    if ( curveType == "Chaikin" ) {
        ui_->pointNum->setEnabled(true);
        chaikinNode_->getModel()->setCount("cpnum", ui_->pointNum->value());
        currentCurve_ = new ChaikinCurve(chaikinNode_);
    } else return;
    currentCurve_->addToScene(graphicsScene_);
}

void MainWindow::changeCurvePointNum(int pointNum)
{
    if ( ui_->pointNum->isEnabled() ) {
        changeCurveType(ui_->curveType->currentText());
    }
}

void MainWindow::changeCurveRecurse(int recurse)
{
    chaikinNode_->getModel()->setCount("recursions", recurse);
    currentCurve_->updateCurvePath();
}

void MainWindow::changeCurvePosX(int posX)
{
    chaikinNode_->setTx(posX);
    currentCurve_->updateControlPoints();
}

void MainWindow::changeCurvePosY(int posY)
{
    chaikinNode_->setTy(posY);
    currentCurve_->updateControlPoints();
}

void MainWindow::changeCurveRot(int rot)
{
    auto rotPi = (M_PI / 1000) * rot;
    chaikinNode_->setRz(rotPi);
    currentCurve_->updateControlPoints();
}
