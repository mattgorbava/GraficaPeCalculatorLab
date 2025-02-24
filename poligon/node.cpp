#include "node.h"

Node::Node()
	: value{-1}
{}

Node::Node(QPointF coordinates)
	: coordinates{coordinates},
	value{-1}
{}

int Node::getCoordX() const
{
	return coordinates.x();
}

int Node::getCoordY() const
{
	return coordinates.y();
}

int Node::getValue() const
{
	return value;
}

QPointF Node::getCoordinates() const
{
	return coordinates;
}

int Node::getAdjacentNodesCounter() const
{
	return adjacentNodesCounter;
}

void Node::setCoordX(int x)
{
	coordinates.setX(x);
}

void Node::setCoordY(int y)
{
	coordinates.setY(y);
}

void Node::setValue(int value)
{
	this->value = value;
}

void Node::setCoordinates(QPointF position)
{
	coordinates = position;
}

void Node::incrementAdjacentNodesCounter()
{
	++adjacentNodesCounter;
}