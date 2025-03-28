#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QInputDialog>
#include "BSpline.h"
#include "node.h"

class BSplineWidget : public QWidget
{
	Q_OBJECT

public:
	explicit BSplineWidget(QWidget* parent = nullptr);

protected:
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
	std::vector<Node*> controlPoints;
	bool isDragging = false;
	Node* draggedNode;
	Node* aux;
	bool saved = false;
	int k = 0;
};