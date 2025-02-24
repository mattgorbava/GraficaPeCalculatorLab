#include "edge.h"

Edge::Edge()
{
	source = new Node();
	destination = new Node();
}

Edge::Edge(Node* source, Node* destination)
	: source{source}, destination{destination}
{}

Node* Edge::getFirstNode() const
{
	return source;
}

Node* Edge::getSecondNode() const
{
	return destination;
}

void Edge::setFirstNode(Node* source)
{
	this->source = source;
}

void Edge::setSecondNode(Node* destination)
{
	this->destination = destination;
}