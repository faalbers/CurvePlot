#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QGraphicsView>

#include "BezierCurve.hpp"
#include "Bezier3PAlgoCurve.hpp"
#include "Bezier4PAlgoCurve.hpp"
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

    // setup chaiking curve
    mh_ = std::make_shared<MH::ModelHierachy>();
    mh_->setFrameAxisY(0.0,-1.0,0.0);
    mh_->setFramePosition(300.0,300.0,0.0);
    auto chaikin = std::make_shared<MH::ChaikinCurve>(ui_->pointNum->value());
    chaikinNode_ = mh_->addModel(chaikin, "Chaikin");
    chaikinNode_->setRz(M_PI/4);

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
    if ( curveType == "Bezier3PAlgo" ) {
        ui_->pointNum->setEnabled(false);
        currentCurve_ = new Bezier3PAlgoCurve;
        ui_->pointNum->setValue(currentCurve_->getControlPointNum());
    } else if ( curveType == "Bezier4PAlgo" ) {
        ui_->pointNum->setEnabled(false);
        currentCurve_ = new Bezier4PAlgoCurve;
        ui_->pointNum->setValue(currentCurve_->getControlPointNum());
    } else if ( curveType == "Bezier" ) {
        ui_->pointNum->setEnabled(true);
        currentCurve_ = new BezierCurve(ui_->pointNum->value());
    } else if ( curveType == "Chaikin" ) {
        ui_->pointNum->setEnabled(true);
        //currentCurve_ = new ChaikinCurve(ui_->pointNum->value());
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
