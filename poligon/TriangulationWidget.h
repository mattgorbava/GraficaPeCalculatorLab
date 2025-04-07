#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QLabel>
#include "Triangulation.h"

class TriangulationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TriangulationWidget(QWidget* parent = nullptr);
    ~TriangulationWidget();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private:
    Polygon polygon;
    Node* draggedNode = new Node();
    Node* firstNode = new Node();
    Node* aux = new Node();
    bool isDragging = false;
    bool polygonSaved = false;

    bool isPolygonClosed();

};