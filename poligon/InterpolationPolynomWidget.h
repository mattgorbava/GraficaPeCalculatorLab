#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "polygon.h"
#include "Polynom.h"

class InterpolationPolynomWidget : public QWidget
{
	Q_OBJECT

public:
	explicit InterpolationPolynomWidget(QWidget* parent = nullptr);
	~InterpolationPolynomWidget();

protected:
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	//virtual void mousePressEvent(QMouseEvent* event) override;
	//virtual void mouseMoveEvent(QMouseEvent* event) override;
	//virtual void resizeEvent(QResizeEvent* event) override;

private:
	Polygon polygon;
	Polynom polynom;

	Node* draggedNode = new Node();
	bool isDragging = false;
	bool polynomSaved = false;

	void computePolygonPointsAndEdges(std::vector<double> coefficients);
	void addNineEmptyNodes();
};
