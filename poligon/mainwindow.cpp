#include "mainwindow.h"
#include <QPainter>
#include <QPalette>

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->resize(800, 600);
    
    toolBar = new QToolBar("Tool Bar", this);
    addToolBar(Qt::TopToolBarArea, toolBar);

    QAction* polygonAction = new QAction("Polygon", this);
    QAction* curvedLineAction = new QAction("Curved Line", this);
    QAction* interpolationPolynomAction = new QAction("Interpolation Polynom", this);
    QAction* bezierAction = new QAction("Bezier", this);
    QAction* hermiteAction = new QAction("Hermite", this);
    QAction* bSplineAction = new QAction("B-Spline", this);
    toolBar->addAction(polygonAction);
    toolBar->addAction(curvedLineAction);
    toolBar->addAction(interpolationPolynomAction);
    toolBar->addAction(bezierAction);
    toolBar->addAction(hermiteAction);
    toolBar->addAction(bSplineAction);

    connect(polygonAction, &QAction::triggered, this, &mainwindow::showPolygonWidget);
    connect(curvedLineAction, &QAction::triggered, this, &mainwindow::showCurvedLineWidget);
    connect(interpolationPolynomAction, &QAction::triggered, this, &mainwindow::showInterpolationPolynomWidget);
    connect(bezierAction, &QAction::triggered, this, &mainwindow::showBezierWidget);
    connect(hermiteAction, &QAction::triggered, this, &mainwindow::showHermiteWidget);
    connect(bSplineAction, &QAction::triggered, this, &mainwindow::showBSplineWidget);

    centralStackedWidget = new QStackedWidget(this);

    polygonWidget = new PolygonWidget(this);
    curvedLineWidget = new CurvedLineWidget(this);
    interpolationPolynomWidget = new InterpolationPolynomWidget(this);
    bezier = new Bezier(this);
    hermite = new Hermite(this);
    bSpline = new BSplineWidget(this);

    centralStackedWidget->addWidget(polygonWidget);
    centralStackedWidget->addWidget(curvedLineWidget);
    centralStackedWidget->addWidget(interpolationPolynomWidget);
    centralStackedWidget->addWidget(bezier);
    centralStackedWidget->addWidget(hermite);
    centralStackedWidget->addWidget(bSpline);

    setCentralWidget(centralStackedWidget);

    showPolygonWidget();
}

mainwindow::~mainwindow()
{}

void mainwindow::showPolygonWidget()
{
    centralStackedWidget->setCurrentWidget(polygonWidget);
    polygonWidget->setFocus();
}

void mainwindow::showCurvedLineWidget()
{
	centralStackedWidget->setCurrentWidget(curvedLineWidget);
	curvedLineWidget->setFocus();
}

void mainwindow::showInterpolationPolynomWidget()
{
	centralStackedWidget->setCurrentWidget(interpolationPolynomWidget);
	interpolationPolynomWidget->setFocus();
}

void mainwindow::showBezierWidget()
{
	centralStackedWidget->setCurrentWidget(bezier);
	bezier->setFocus();
}

void mainwindow::showHermiteWidget()
{
	centralStackedWidget->setCurrentWidget(hermite);
	hermite->setFocus();
}

void mainwindow::showBSplineWidget()
{
	centralStackedWidget->setCurrentWidget(bSpline);
	bSpline->setFocus();
}