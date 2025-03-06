#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QLabel>
#include "polygon.h"
#include "Transformare.h"

class PolygonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PolygonWidget(QWidget* parent = nullptr);
    ~PolygonWidget();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;

private:
    bool rKeyPressed = false; //rotate
    bool tKeyPressed = false; //translate

    QPoint mouseLastPosition;

    Polygon polygon;
    Node* draggedNode = new Node();
    Node* firstNode = new Node();
    Node* aux = new Node();
    bool isDragging = false;
    bool polygonSaved = false;

    bool isPolygonClosed();

    QLabel* titleLabel;
};