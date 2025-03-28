#include "InterpolationPolynomWidget.h"

InterpolationPolynomWidget::InterpolationPolynomWidget(QWidget* parent)
	: QWidget(parent)
{
	newtonButton = new QPushButton("Newton", this);
	newtonButton->setGeometry(10, 10, 100, 30);
	connect(newtonButton, SIGNAL(clicked()), this, SLOT(newtonButtonClicked()));

	lagrangeButton = new QPushButton("Lagrange", this);
	lagrangeButton->setGeometry(120, 10, 100, 30);
	connect(lagrangeButton, SIGNAL(clicked()), this, SLOT(lagrangeButtonClicked()));
}

void InterpolationPolynomWidget::newtonButtonClicked()
{
	if (!polynomSaved)
		popLastNine();
	interpolationType = InterpolationType::Newton;
	polynom.computeCoefficientsNewton(initialNodes);
	computePolygonPointsAndEdges(polynom.getCoefficients());
	polynomSaved = true;
	update();
}

void InterpolationPolynomWidget::lagrangeButtonClicked()
{
	if (!polynomSaved)
		popLastNine();
	interpolationType = InterpolationType::Lagrange;
	polynom.computeCoefficientsLagrange(initialNodes);
	computePolygonPointsAndEdges(polynom.getCoefficients());
	polynomSaved = true;
	update();
}

InterpolationPolynomWidget::~InterpolationPolynomWidget()
{ }

void InterpolationPolynomWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (!polynomSaved)
	{
		if (event->button() == Qt::LeftButton && event->pos().x() > lastX)
		{
			polygon.addNode(event->pos());
			lastX = event->pos().x();
			initialNodes.push_back(new Node(event->pos()));
			addNineEmptyNodes();
			update();
		}
	}
	else
	{
		if (event->button() == Qt::LeftButton)
		{
			draggedNode = aux;
			draggedInitialNode = aux;
			isDragging = false;
		}
	}
}

void InterpolationPolynomWidget::computePolygonPointsAndEdges(std::vector<double> coefficients)
{
	std::vector<Node*> nodes = polygon.getNodes();
	std::vector<Edge*> edges = polygon.getEdges();

	polygon.clearEdges();
	for (int i = 0; i < nodes.size(); i++)
	{
		double xBetween;
		if (i % 10 == 0 && i != nodes.size() - 1)
		{
			xBetween = (nodes[i + 10]->getCoordX() - nodes[i]->getCoordX()) / 10.0;
		}
		if (i % 10 != 0)
		{
			double x = nodes[i - 1]->getCoordX() + xBetween;
			double y = 0.0;
			switch (interpolationType)
			{
			case InterpolationPolynomWidget::InterpolationType::Newton:
				y = polynom.computeValueNewton(x, initialNodes);
				break;
			case InterpolationPolynomWidget::InterpolationType::Lagrange:
				y = polynom.computeValueLagrange(x, initialNodes);
				break;
			default:
				break;
			}
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

	for (int i = 0; i < nodes.size(); i+=10)
	{
		painter.setBrush(Qt::black);
		painter.drawEllipse(nodes[i]->getCoordinates(), 5, 5);
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

void InterpolationPolynomWidget::mousePressEvent(QMouseEvent* e)
{
	if (polynomSaved)
	{
		std::vector<Node*> nodes = polygon.getNodes();
		for (int i = 0; i < nodes.size(); i+=10)
		{
			if (fabs(nodes[i]->getCoordX() - e->pos().x()) < 10 && fabs(nodes[i]->getCoordY() - e->pos().y()) < 10)
			{
				draggedNode = nodes[i];
				draggedInitialNode = initialNodes[i / 10];
				isDragging = true;
				break;
			}
		}
	}
}

void InterpolationPolynomWidget::mouseMoveEvent(QMouseEvent* e)
{
	if (isDragging)
	{
		draggedNode->setCoordinates(e->pos());
		draggedInitialNode->setCoordinates(e->pos());
		switch (interpolationType)
		{
		case InterpolationPolynomWidget::InterpolationType::Newton:
			polynom.computeCoefficientsNewton(initialNodes);
			break;
		case InterpolationPolynomWidget::InterpolationType::Lagrange:
			polynom.computeCoefficientsLagrange(initialNodes);
			break;
		default:
			break;
		}
		computePolygonPointsAndEdges(polynom.getCoefficients());
		update();
	}
}

void InterpolationPolynomWidget::addNineEmptyNodes()
{
	for (int i = 0; i < 9; i++)
	{
		polygon.addNode(QPoint(-1, -1));
	}
}

void InterpolationPolynomWidget::popLastNine()
{
	for (int i = 0; i < 9; i++)
	{
		polygon.popBack();
	}
}