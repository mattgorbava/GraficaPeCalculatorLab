#pragma once

#include "polygon.h"
#include "ui_mainwindow.h"
#include "Transformare.h"
#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPushButton>
#include <QLine>
#include <QLabel>
#include <QSlider>

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    ~mainwindow();

private:
    bool rKeyPressed = false; //rotate
    bool tKeyPressed = false; //translate

    QPoint mouseLastPosition;

    Ui::mainwindowClass ui;
    Polygon polygon;
    Node* draggedNode = new Node();
    Node* firstNode = new Node();
    Node* aux = new Node();
    bool isDragging = false;
    bool polygonSaved = false;

    bool isPolygonClosed();

    double rotationAngle = 0;
    double scaleX = 1;
    double scaleY = 1;
};
