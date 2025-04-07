#pragma once
#include "polygon.h"
#include "ComputationalGeometry.h"

class Triangulation {
public:
	static std::vector<Edge*> triangulate(Polygon polygon, std::vector<Edge*>& diagonals) {
		std::vector<Node*> nodes = polygon.getNodes();
		std::vector<Edge*> edges = polygon.getEdges();

		if (nodes.size() <= 3) {
			return diagonals;
		}

		else {
			int indexMin = findMinimumNode(polygon);
			int index1 = indexMin == 0 ? nodes.size() - 1 : indexMin - 1;
			int index2 = indexMin == nodes.size() - 1 ? 0 : indexMin + 1;

			Polygon triangle = createTriangle(polygon, index1, indexMin, index2);

			int indexMinInTriangle = findMinimumNodeInTriangle(polygon, triangle);
			if (indexMinInTriangle == -1) {
				diagonals.push_back(new Edge(nodes[index1], nodes[index2]));
				Polygon p1, p2;

				p1 = createPolygon(polygon, index1, index2);
				p2 = createPolygon(polygon, index2, index1);

				triangulate(p1, diagonals);
				triangulate(p2, diagonals);
			}
			else {
				diagonals.push_back(new Edge(nodes[indexMin], nodes[indexMinInTriangle]));
				Polygon p1, p2;

				p1 = createPolygon(polygon, indexMin, indexMinInTriangle);
				p2 = createPolygon(polygon, indexMinInTriangle, indexMin);

				triangulate(p1, diagonals);
				triangulate(p2, diagonals);
			}
		}

		return diagonals;
	}

private:
	static int findMinimumNode(Polygon p) {
		std::vector<Node*> nodes = p.getNodes();

		int indexMin = 0;
		for (int i = 0; i < nodes.size(); ++i) {
			if (nodes[i]->getCoordY() < nodes[indexMin]->getCoordY()) {
				indexMin = i;
			}
			else if (nodes[i]->getCoordY() == nodes[indexMin]->getCoordY() &&
				nodes[i]->getCoordX() < nodes[indexMin]->getCoordX()) {
				indexMin = i;
			}
		}
		return indexMin;
	}

	static Polygon createTriangle(Polygon p, int index1, int indexMin, int index2) {
		std::vector<Node*> nodes = p.getNodes();

		Polygon triangle;
		triangle.addNode(nodes[indexMin]);
		triangle.addNode(nodes[index1]);
		triangle.addNode(nodes[index2]);
		triangle.addEdge(nodes[index1], nodes[indexMin]);
		triangle.addEdge(nodes[indexMin], nodes[index2]);
		triangle.addEdge(nodes[index2], nodes[index1]);

		return triangle;
	}

	static int findMinimumNodeInTriangle(Polygon p, Polygon triangle) {
		int nodeIndex = -1;

		std::vector<Node*> nodes = p.getNodes();

		for (int i = 0; i < nodes.size(); ++i) {
			std::vector<Node*> triangleNodes = triangle.getNodes();
			bool isTriangleNode = false;
			for (int j = 0; j < triangleNodes.size(); ++j) {
				if (nodes[i] == triangleNodes[j]) {
					isTriangleNode = true;
				}
			}

			if (isTriangleNode) continue;

			if (ComputationalGeometry::pointInConvexPolygon(nodes[i]->getCoordinates(), triangle)) {
				if (nodeIndex != -1 && nodes[i]->getCoordY() < nodes[nodeIndex]->getCoordY()) {
					nodeIndex = i;
				}
				else if (nodeIndex == -1) nodeIndex = i;
			}
		}

		return nodeIndex;
	}

	static Polygon createPolygon(Polygon p, int index1, int index2) {
		Polygon result;

		std::vector<Node*> nodes = p.getNodes();
		if (index1 < index2) {
			for (int i = index1; i <= index2; ++i) {
				result.addNode(nodes[i]);
			}
			std::vector<Node*> resultNodes = result.getNodes();
			for (int i = 0; i < resultNodes.size() - 1; ++i) {
				result.addEdge(resultNodes[i], resultNodes[i + 1]);
			}
			result.addEdge(resultNodes[resultNodes.size() - 1], resultNodes[0]);
		}
		else {
			for (int i = index1; i < nodes.size(); ++i) {
				result.addNode(nodes[i]);
			}
			for (int i = 0; i <= index2; ++i) {
				result.addNode(nodes[i]);
			}
			std::vector<Node*>resultNodes = result.getNodes();
			for (int i = 0; i < resultNodes.size() - 1; ++i) {
				result.addEdge(resultNodes[i], resultNodes[i + 1]);
			}
			result.addEdge(resultNodes[resultNodes.size() - 1], resultNodes[0]);
		}
		
		return result;
	}
};