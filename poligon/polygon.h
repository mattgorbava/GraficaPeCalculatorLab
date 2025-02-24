#pragma once

#include "edge.h"

class Polygon
{
public:
	Polygon();
	~Polygon() = default;

	void addNode(QPoint coordinates);
	void addNode(Node* node);
	void addEdge(Node* source, Node* destination);
	void addEdge(Edge* edge);
	void computeCenterOfMass();

	std::vector<Node*> getNodes() const;
	std::vector<Edge*> getEdges() const;
	QPoint getCenterOfMass() const;
private:
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	QPoint centerOfMass;
};