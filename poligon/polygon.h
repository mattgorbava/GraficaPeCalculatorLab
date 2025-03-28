#pragma once

#include "edge.h"

class Polygon
{
public:
	Polygon();
	~Polygon() = default;

	void addNode(QPointF coordinates);
	void addNode(Node* node);
	void addEdge(Node* source, Node* destination);
	void addEdge(Edge* edge);
	void computeCenterOfMass();
	void popBack();
	void clearEdges();

	std::vector<Node*> getNodes() const;
	std::vector<Edge*> getEdges() const;
	QPointF getCenterOfMass() const;
private:
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	QPointF centerOfMass;
};