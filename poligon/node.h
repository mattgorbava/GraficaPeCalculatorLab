#pragma once

#include <QPointF>
#include <QGraphicsItem>

class Node
{
public:
	Node();
	Node(QPointF coordinates);
	~Node() = default;

	int getCoordX() const;
	int getCoordY() const;
	int getValue() const;
	QPointF getCoordinates() const;
	int getAdjacentNodesCounter() const;

	void setCoordX(int x);
	void setCoordY(int y);
	void setValue(int value);
	void setCoordinates(QPointF position);
	void incrementAdjacentNodesCounter();

private:
	QPointF coordinates;
	int value;
	int adjacentNodesCounter = 0;
};