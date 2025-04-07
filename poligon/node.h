#pragma once

#include <QPointF>
#include <QGraphicsItem>

class Node
{
public:
	Node();
	Node(QPointF coordinates);
	~Node() = default;

	bool operator==(const Node* other) const {
		return (this->coordinates.x() == other->coordinates.x() &&
			this->coordinates.y() == other->coordinates.y());
	}

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