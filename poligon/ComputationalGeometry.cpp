#include "ComputationalGeometry.h"

double ComputationalGeometry::F(QPointF A, QPointF B, QPointF C)
{
	return (B.x() - A.x()) * (C.y() - A.y()) - (B.y() - A.y()) * (C.x() - A.x());
}

int ComputationalGeometry::sgn(double x)
{
	double EPSILON = 1e-9;
	if (x > EPSILON) return 1;
	if (x < -EPSILON) return -1;
	return 0;
}

bool ComputationalGeometry::sameSideOfLine(QPointF A, QPointF B, QPointF C, QPointF D)
{
	return F(C, D, A) * F(C, D, B) > 0;
}

bool ComputationalGeometry::convexQuadrilateral(QPointF A, QPointF B, QPointF C, QPointF D)
{
	return (sgn(F(A, B, C)) == sgn(F(B, C, D))) &&
		(sgn(F(B, C, D)) == sgn(F(C, D, A))) &&
		(sgn(F(C, D, A)) == sgn(F(D, A, B)));
}

bool ComputationalGeometry::pointInTriangle(QPointF A, QPointF B, QPointF C, QPointF D)
{
	return (sgn(F(B, C, A)) == sgn(F(C, A, D))) &&
		(sgn(F(C, A, D)) == sgn(F(A, D, B)));
}

bool ComputationalGeometry::pointInConvexPolygon(QPointF A, Polygon p)
{
	std::vector<Node*> nodes = p.getNodes();
	int sign = sgn(F(nodes[0]->getCoordinates(), nodes[1]->getCoordinates(), A));
	for (int i = 1; i < nodes.size(); i++)
	{
		if (sign != sgn(F(nodes[i]->getCoordinates(), nodes[(i + 1) % nodes.size()]->getCoordinates(), A)))
		{
			return false;
		}
	}
	return true;
}

bool ComputationalGeometry::convexPolygon(Polygon p)
{
	std::vector<Node*> nodes = p.getNodes();
	int n = nodes.size();
	int sign = sgn(F(nodes[0]->getCoordinates(), nodes[1]->getCoordinates(), nodes[2]->getCoordinates()));
	for (int i = 1; i < n; i++)
	{
		if (sign != sgn(
			F(nodes[i]->getCoordinates(), nodes[(i + 1) % n]->getCoordinates(), nodes[(i + 2) % n]->getCoordinates())
		))
		{
			return false;
		}
	}
	return true;
}

bool ComputationalGeometry::noIntersection(QPointF A, QPointF B, QPointF C, QPointF D)
{
	return convexQuadrilateral(A, D, B, C);
}

bool ComputationalGeometry::pointInPolygon(QPointF A, Polygon p)
{
	int numIntersections = 0;
	std::vector<Node*> nodes = p.getNodes();
	std::vector<Edge*> edges = p.getEdges();

	double maxX = 0, maxY = 0;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->getCoordinates().x() > maxX)
		{
			maxX = nodes[i]->getCoordinates().x();
		}
		if (nodes[i]->getCoordinates().y() > maxY)
		{
			maxY = nodes[i]->getCoordinates().y();
		}
	}
	
	QPointF outside(maxX + 1, maxY + 1);
	for (int i = 0; i < edges.size(); i++)
	{
		if (!noIntersection(A, outside, edges[i]->getFirstNode()->getCoordinates(), 
			edges[i]->getSecondNode()->getCoordinates()))
		{
			numIntersections++;
		}
	}
	return numIntersections % 2 == 1;
}