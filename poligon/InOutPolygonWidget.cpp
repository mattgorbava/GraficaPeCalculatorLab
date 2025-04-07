#include "InOutPolygonWidget.h"

InOutPolygonWidget::InOutPolygonWidget(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);
}

void InOutPolygonWidget::mouseReleaseEvent(QMouseEvent* e)
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
                            int maxX = 0, maxY = 0;
                            for (auto& node : nodes)
							{
								if (node->getCoordX() > maxX)
									maxX = node->getCoordX();
								if (node->getCoordY() > maxY)
									maxY = node->getCoordY();
							}
                            outside.setX(maxX + 1);
							outside.setY(maxY + 1);
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

void InOutPolygonWidget::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    if (polygonSaved)
    {
        QRect rectangle(outside.x() - 10, outside.y() - 10, 20, 20);
        painter.drawEllipse(rectangle);
        int width = this->width();
        int height = this->height();

        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                QPointF point(x, y);
                if (ComputationalGeometry::pointInPolygon(point, polygon))
                {
                    painter.setPen(Qt::red);
                    painter.drawPoint(x, y);
                }
                else
                {
                    painter.setPen(Qt::green);
                    painter.drawPoint(x, y);
                }
            }
        }
    }

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

void InOutPolygonWidget::mouseMoveEvent(QMouseEvent* e)
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
}

void InOutPolygonWidget::mousePressEvent(QMouseEvent* e)
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

bool InOutPolygonWidget::isPolygonClosed()
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