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
    ~mainwindow();

private slots:
    void onRotationSliderChanged(int value);
    void onTranslationXSliderChanged(int value);
    void onTranslationYSliderChanged(int value);
    void onScalingXSliderChanged(int value);
    void onScalingYSliderChanged(int value);

private:
    void initializeSliders();
    bool initialized = false;

    bool shiftPressed = false;

    QPoint mouseLastPosition;

    Ui::mainwindowClass ui;
    Polygon polygon;
    Node* draggedNode = new Node();
    Node* firstNode = new Node();
    Node* aux = new Node();
    bool isDragging = false;
    bool polygonSaved = false;

    bool isPolygonClosed();

    QPushButton clearButton;

    //graphical elements
    QLine oX = QLine(30, 300, 770, 300);
    QLine oY = QLine(400, 570, 400, 30);
    QLine xArrow = QLine(770, 300, 760, 290);
    QLine yArrow = QLine(400, 570, 410, 560);
    QLine xArrow2 = QLine(770, 300, 760, 310);
    QLine yArrow2 = QLine(400, 570, 390, 560);
    QLabel xLabel = QLabel("x");
    QLabel yLabel = QLabel("y");
    QLabel oLabel = QLabel("O");
    QLabel rotationLabel = QLabel("Rotation");
    QLabel translationXLabel = QLabel("Translation X");
    QLabel translationYLabel = QLabel("Translation Y");
    QLabel scalingXLabel = QLabel("Scaling X");
    QLabel scalingYLabel = QLabel("Scaling Y");

    //transformations
    QSlider rotationSlider;
    QSlider translationXSlider;
    QSlider translationYSlider;
    QSlider scalingXSlider;
    QSlider scalingYSlider;

    double rotationAngle = 0;
    double scaleX = 1;
    double scaleY = 1;
};
