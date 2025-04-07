#pragma once
#include <QPointF>
#include <cmath>
#include "polygon.h"

class ComputationalGeometry
{
private:
	static double F(QPointF A, QPointF B, QPointF C);
	static int sgn(double x);

public:
	static bool sameSideOfLine(QPointF A, QPointF B, QPointF C, QPointF D);
	static bool convexQuadrilateral(QPointF A, QPointF B, QPointF C, QPointF D);
	static bool pointInTriangle(QPointF A, QPointF B, QPointF C, QPointF D);
	static bool pointInConvexPolygon(QPointF A, Polygon p);
	static bool convexPolygon(Polygon p);
	static bool noIntersection(QPointF A, QPointF B, QPointF C, QPointF D);
	static bool pointInPolygon(QPointF A, Polygon p);
};