#include "PolygonWidget.h"

PolygonWidget::PolygonWidget(QWidget* parent)
	: QWidget(parent)
{
	setMouseTracking(true);

    titleLabel = new QLabel("Tema 1", this);
    titleLabel->setGeometry(15, 15, 100, 20);
    titleLabel->setFont(QFont("Arial", 20, 10));
    titleLabel->show();
}

PolygonWidget::~PolygonWidget()
{
}

void PolygonWidget::mouseReleaseEvent(QMouseEvent* e)
{
    if (!polygonSaved)
    {
        std::vector<Node*> nodes = polygon.getNodes();
        std::vector<Edge*> edges = polygon.getEdges();

        if (e->button() == Qt::RightButton)
        {
            bool addNode = true;

            for (auto& node : nodes)
                if (fabs(node->getCoordX() - e->pos().x()) < 20 && fabs(node->getCoordY() - e->pos().y()) < 20)
                    addNode = false;

            if (addNode)
            {
                polygon.addNode(e->pos());
                update();
            }
        }

        if (e->button() == Qt::LeftButton)
        {
            for (auto& node : nodes)
            {
                if (fabs(node->getCoordX() - e->pos().x()) < 10 && fabs(node->getCoordY() - e->pos().y()) < 10)
                {
                    if (firstNode->getValue() == -1)
                        firstNode = node;
                    else
                    {
                        QPointF point1 = firstNode->getCoordinates();
                        QPointF point2 = node->getCoordinates();
                        if (firstNode == node)
                            break;
                        if (firstNode->getAdjacentNodesCounter() >= 2 || node->getAdjacentNodesCounter() >= 2)
                            break;
                        polygon.addEdge(firstNode, node);
                        if (isPolygonClosed())
                        {
                            polygonSaved = true;
                        }
                        firstNode = aux;
                    }
                    break;
                }
                else if (firstNode->getValue() != -1 && node->getValue() == nodes.size())
                {
                    firstNode = aux;
                }
            }
            isDragging = false;
            update();
        }
    }
}

void PolygonWidget::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    std::vector<Node*> nodes = polygon.getNodes();
    std::vector<Edge*> edges = polygon.getEdges();

    if (!polygonSaved)
    {
        for (auto& node : nodes)
        {
            QRect rectangle(node->getCoordX() - 10, node->getCoordY() - 10, 20, 20);
            painter.drawEllipse(rectangle);
            QString s;
            s.setNum(node->getValue());
            painter.drawText(rectangle, Qt::AlignCenter, s);
        }
    }

    for (auto& edge : edges)
    {

        if (!polygonSaved)
        {
            double unghiulDreptei{ atan2(edge->getSecondNode()->getCoordY() - edge->getFirstNode()->getCoordY(),
                                        edge->getSecondNode()->getCoordX() - edge->getFirstNode()->getCoordX()) };
            double lungimePeAxaX1{ cos(unghiulDreptei) * 10 };// pt muchie
            double lungimePeAxaY1{ sin(unghiulDreptei) * 10 };// pt muchie

            painter.drawLine(edge->getFirstNode()->getCoordX() + lungimePeAxaX1, edge->getFirstNode()->getCoordY() + lungimePeAxaY1,
                edge->getSecondNode()->getCoordX() - lungimePeAxaX1, edge->getSecondNode()->getCoordY() - lungimePeAxaY1);
        }
        else
        {
            painter.drawLine(edge->getFirstNode()->getCoordX(), edge->getFirstNode()->getCoordY(),
                edge->getSecondNode()->getCoordX(), edge->getSecondNode()->getCoordY());
        }
    }

    if (!polygonSaved)
    {
        if (firstNode->getValue() != -1)
        {
            QRect rectangle(firstNode->getCoordX() - 10, firstNode->getCoordY() - 10, 20, 20);
            QPen pen;
            pen.setColor(Qt::red);
            pen.setWidth(2);
            painter.setPen(pen);
            painter.drawEllipse(rectangle);
            QString s;
            s.setNum(firstNode->getValue());
            painter.drawText(rectangle, Qt::AlignCenter, s);
        }
    }
}

void PolygonWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (!polygonSaved)
    {
        QPoint mousePos = e->pos();
        if (isDragging && draggedNode)
        {
            draggedNode->setCoordinates(mousePos);
            firstNode = aux;
            update();
        }
    }
    else
    {
        if (rKeyPressed)
        {
            double angle = e->pos().x() - mouseLastPosition.x();
            polygon.computeCenterOfMass();
            QPointF centerOfMass = polygon.getCenterOfMass();
            for (auto& node : polygon.getNodes())
            {
                node->setCoordinates(Transformare::rotatePointAroundPoint(node->getCoordinates(), centerOfMass, angle));
            }
            update();
        }
        else if (tKeyPressed)
        {
            double translationX = (e->pos().x() - mouseLastPosition.x());
            double translationY = (e->pos().y() - mouseLastPosition.y());
            for (auto& node : polygon.getNodes())
            {
                node->setCoordinates(Transformare::translatePoint(node->getCoordinates(), translationX, translationY));
            }
            update();
        }
    }
    mouseLastPosition = e->pos();
}

void PolygonWidget::wheelEvent(QWheelEvent* e)
{
    if (polygonSaved)
    {
        polygon.computeCenterOfMass();
        QPointF centerOfMass = polygon.getCenterOfMass();
        if (e->angleDelta().y() > 0)
        {
            for (auto& node : polygon.getNodes())
            {
                node->setCoordinates(Transformare::scalePointAroundPoint(node->getCoordinates(), centerOfMass, 1.1, 1.1));
            }
            update();
        }
        else
        {
            for (auto& node : polygon.getNodes())
            {
                node->setCoordinates(Transformare::scalePointAroundPoint(node->getCoordinates(), centerOfMass, 0.9, 0.9));
            }
            update();
        }
    }
}

void PolygonWidget::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_R)
	{
		rKeyPressed = true;
        qDebug() << "R key pressed";
	}
	else if (e->key() == Qt::Key_T)
	{
		tKeyPressed = true;
        qDebug() << "T key pressed";
	}
}

void PolygonWidget::keyReleaseEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_R)
	{
		rKeyPressed = false;
	}
	else if (e->key() == Qt::Key_T)
	{
		tKeyPressed = false;
	}
}

void PolygonWidget::mousePressEvent(QMouseEvent* e)
{
	if (!polygonSaved)
	{
		std::vector<Node*> nodes = polygon.getNodes();
		for (auto& node : nodes)
		{
			if (fabs(node->getCoordX() - e->pos().x()) < 10 && fabs(node->getCoordY() - e->pos().y()) < 10)
			{
				draggedNode = node;
				isDragging = true;
				break;
			}
		}
	}
}

bool PolygonWidget::isPolygonClosed()
{
	std::vector<Node*> nodes = polygon.getNodes();
	std::vector<Edge*> edges = polygon.getEdges();
	int counter = 0;
	for (auto& node : nodes)
	{
		for (auto& edge : edges)
		{
			if (node == edge->getFirstNode() || node == edge->getSecondNode())
				counter++;
		}
		if (counter < 2)
			return false;
		counter = 0;
	}
	return true;
}