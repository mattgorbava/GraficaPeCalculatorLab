#include "InterpolationPolynomWidget.h"

InterpolationPolynomWidget::InterpolationPolynomWidget(QWidget* parent)
	: QWidget(parent)
{ }

InterpolationPolynomWidget::~InterpolationPolynomWidget()
{ }

void InterpolationPolynomWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (!polynomSaved)
	{
		if (event->button() == Qt::LeftButton)
		{
			polygon.addNode(event->pos());
			addNineEmptyNodes();
			update();
		}
		if (event->button() == Qt::RightButton)
		{
			polynomSaved = true;
			polynom = Polynom(polygon);
			update();
		}
	}
}

void InterpolationPolynomWidget::computePolygonPointsAndEdges(std::vector<double> coefficients)
{
	std::vector<Node*> nodes = polygon.getNodes();
	std::vector<Edge*> edges = polygon.getEdges();

	for (int i = 0; i < nodes.size(); i++)
	{
		if (i % 10 != 0)
		{
			double xBetween = (nodes[i / 10]->getCoordX() + nodes[i / 10 + 10]->getCoordX()) / 10.0;
			double x = nodes[i - 1]->getCoordX() + xBetween;
			double y = polynom.computeValue(x);
			nodes[i]->setCoordinates(QPointF(x, y));
		}
	}

	for (int i = 0; i < nodes.size() - 1; i++)
	{
		polygon.addEdge(nodes[i], nodes[i + 1]);
	}
}

void InterpolationPolynomWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	std::vector<Node*> nodes = polygon.getNodes();
	std::vector<Edge*> edges = polygon.getEdges();

	if (nodes.size() > 0)
	{
		for (auto& node : nodes)
		{
			if (node->getCoordX() != -1 && node->getCoordY() != -1)
			{
				painter.setBrush(Qt::black);
				painter.drawEllipse(node->getCoordinates(), 5, 5);
			}
		}
	}
	if (edges.size() > 0)
	{
		for (auto& edge : edges)
		{
			if (edge->getFirstNode()->getCoordX() != -1 && edge->getFirstNode()->getCoordY() != -1 &&
				edge->getSecondNode()->getCoordX() != -1 && edge->getSecondNode()->getCoordY() != -1)
			{
				painter.setPen(Qt::black);
				painter.drawLine(edge->getFirstNode()->getCoordinates(), edge->getSecondNode()->getCoordinates());
			}
		}
	}
}

void InterpolationPolynomWidget::addNineEmptyNodes()
{
	for (int i = 0; i < 10; i++)
	{
		polygon.addNode(QPoint(-1, -1));
	}
}