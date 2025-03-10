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
    toolBar->addAction(polygonAction);
    toolBar->addAction(curvedLineAction);

    connect(polygonAction, &QAction::triggered, this, &mainwindow::showPolygonWidget);
    connect(curvedLineAction, &QAction::triggered, this, &mainwindow::showCurvedLineWidget);

    centralStackedWidget = new QStackedWidget(this);

    polygonWidget = new PolygonWidget(this);
    curvedLineWidget = new CurvedLineWidget(this);

    centralStackedWidget->addWidget(polygonWidget);
    centralStackedWidget->addWidget(curvedLineWidget);

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