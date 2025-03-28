#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>

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
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	//virtual void resizeEvent(QResizeEvent* event) override;

private slots:
	void newtonButtonClicked();
	void lagrangeButtonClicked();

private:
	enum class InterpolationType
	{
		Newton,
		Lagrange
	};

	Polygon polygon;
	Polynom polynom;
	std::vector<Node*> initialNodes;

	Node* draggedNode = new Node();
	Node* draggedInitialNode = new Node();
	Node* aux = new Node();
	bool isDragging = false;
	bool polynomSaved = false;
	double lastX = 0;
	QPushButton* newtonButton;
	QPushButton* lagrangeButton;
	InterpolationType interpolationType = InterpolationType::Newton;

	void computePolygonPointsAndEdges(std::vector<double> coefficients);
	void addNineEmptyNodes();
	void popLastNine();
};
