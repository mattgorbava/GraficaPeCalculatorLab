#include "polygon.h"

Polygon::Polygon()
{}

void Polygon::addNode(QPointF coordinates)
{
	Node* node = new Node(coordinates);
	node->setValue(nodes.size() + 1);
	nodes.push_back(node);
}

void Polygon::addNode(Node* node)
{
	nodes.push_back(node);
}

void Polygon::addEdge(Edge* edge)
{
	edges.push_back(edge);
	edge->getFirstNode()->incrementAdjacentNodesCounter();
	edge->getSecondNode()->incrementAdjacentNodesCounter();
}

void Polygon::addEdge(Node* source, Node* destination)
{
	edges.push_back(new Edge(source, destination));
	source->incrementAdjacentNodesCounter();
	destination->incrementAdjacentNodesCounter();
}

std::vector<Node*> Polygon::getNodes() const
{
	return nodes;
}

std::vector<Edge*> Polygon::getEdges() const
{
	return edges;
}

void Polygon::computeCenterOfMass()
{
	centerOfMass = QPointF(0, 0);
	for (Node* node : nodes)
	{
		centerOfMass.setX(centerOfMass.x() + node->getCoordX());
		centerOfMass.setY(centerOfMass.y() + node->getCoordY());
	}
	centerOfMass.setX(centerOfMass.x() / nodes.size());
	centerOfMass.setY(centerOfMass.y() / nodes.size());
}

QPointF Polygon::getCenterOfMass() const
{
	return centerOfMass;
}

void Polygon::popBack()
{
	if (!nodes.empty())
	{
		nodes.pop_back();
	}
}

void Polygon::clearEdges()
{
	edges.clear();
}
