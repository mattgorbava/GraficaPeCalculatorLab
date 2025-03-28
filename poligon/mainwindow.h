#pragma once

#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <QActionGroup>
#include "PolygonWidget.h"
#include "CurvedLineWidget.h"
#include "InterpolationPolynomWidget.h"
#include "Bezier.h"
#include "Hermite.h"
#include "BSplineWidget.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private slots:
    void showPolygonWidget();
    void showCurvedLineWidget();
    void showInterpolationPolynomWidget();
    void showBezierWidget();
    void showHermiteWidget();
    void showBSplineWidget();

private:
    Ui::mainwindowClass ui;
    QToolBar* toolBar;
    QStackedWidget* centralStackedWidget;
    PolygonWidget* polygonWidget;
    CurvedLineWidget* curvedLineWidget;
    InterpolationPolynomWidget* interpolationPolynomWidget;
    Bezier* bezier;
    Hermite* hermite;
    BSplineWidget* bSpline;
};
