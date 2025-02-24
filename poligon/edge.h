#pragma once

#include "node.h"

class Edge
{
public:
	Edge();
	Edge(Node* source, Node* destination);
	~Edge() = default;

	Node* getFirstNode() const;
	Node* getSecondNode() const;

	void setFirstNode(Node* source);
	void setSecondNode(Node* destination);

private:
	Node* source;
	Node* destination;
};