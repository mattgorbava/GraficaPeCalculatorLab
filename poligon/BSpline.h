#pragma once
#include <vector>
#include <QPointF>
#include "node.h"

class BSpline
{
public:
	static double basisFunction(int i, int k, double u, std::vector<double> knots);

	static std::vector<double> generateUniformKnotVector(int n, int k);

	static QPointF computeBSplinePoint(double t, const std::vector<QPointF>& controlPoints, int k);

	static std::vector<QPointF> computeBSplineCurve(const std::vector<Node*> controlPoints, int k);

private:
};