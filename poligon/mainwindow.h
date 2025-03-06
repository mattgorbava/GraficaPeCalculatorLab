#pragma once

#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <QActionGroup>
#include "PolygonWidget.h"
#include "CurvedLineWidget.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private slots:
    void showPolygonWidget();
    void showCurvedLineWidget();

private:
    Ui::mainwindowClass ui;
    QToolBar* toolBar;
    QStackedWidget* centralStackedWidget;
    PolygonWidget* polygonWidget;
    CurvedLineWidget* curvedLineWidget;
};
