#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "polygon.h"
#include "ComputationalGeometry.h"

class InOutPolygonWidget : public QWidget
{
	Q_OBJECT

public:
	explicit InOutPolygonWidget(QWidget* parent = nullptr);
	~InOutPolygonWidget() = default;

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
    QPointF outside;

    bool isPolygonClosed();
};