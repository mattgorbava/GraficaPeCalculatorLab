#pragma once

#include <QPoint>
#include <QGraphicsItem>

class Node
{
public:
	Node();
	Node(QPoint coordinates);
	~Node() = default;

	int getCoordX() const;
	int getCoordY() const;
	int getValue() const;
	QPoint getCoordinates() const;
	int getAdjacentNodesCounter() const;

	void setCoordX(int x);
	void setCoordY(int y);
	void setValue(int value);
	void setCoordinates(QPoint position);
	void incrementAdjacentNodesCounter();

private:
	QPoint coordinates;
	int value;
	int adjacentNodesCounter = 0;
};