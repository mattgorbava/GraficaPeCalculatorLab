#include "BSpline.h"

double BSpline::basisFunction(int i, int k, double u, std::vector<double> knots)
{
    if (k == 1)
    {
        if (i < knots.size() - 1 && knots[i] <= u && u < knots[i + 1])
        {
            return 1.0;
        }
        return 0.0;
    }

    double first = 0.0;
    double second = 0.0;

    if (i < knots.size() - (k - 1) && knots[i + k - 1] - knots[i] != 0)
    {
        first = (u - knots[i]) / (knots[i + k - 1] - knots[i])
            * basisFunction(i, k - 1, u, knots);
    }

    if (i + 1 < knots.size() - (k - 2) && knots[i + k] - knots[i + 1] != 0)
    {
        second = (knots[i + k] - u) / (knots[i + k] - knots[i + 1])
            * basisFunction(i + 1, k - 1, u, knots);
    }

    return first + second;
}

std::vector<double> BSpline::generateUniformKnotVector(int n, int k)
{
    std::vector<double> knots;

    for (int i = 0; i < n + k; i++)
	{
		knots.push_back(((double)i)/(n + k - 1));
	}

    return knots;
}

QPointF BSpline::computeBSplinePoint(double t, const std::vector<QPointF>& controlPoints, int k)
{
	std::vector<double> knots = generateUniformKnotVector(controlPoints.size(), k);
	QPointF point(0, 0);

	for (int i = 0; i < controlPoints.size(); i++)
	{
		point.setX(point.x() + controlPoints[i].x() * basisFunction(i, k, t, knots));
		point.setY(point.y() + controlPoints[i].y() * basisFunction(i, k, t, knots));
 	}

	return point;
}

std::vector<QPointF> BSpline::computeBSplineCurve(const std::vector<Node*> controlPoints, int k)
{
	std::vector<QPointF> curvePoints;
	int n = controlPoints.size() - 1;
	std::vector<QPointF> controlPointsQPoint;
    std::vector<double> knots = generateUniformKnotVector(controlPoints.size(), k);

	for (auto node : controlPoints)
	{
		controlPointsQPoint.push_back(node->getCoordinates());
	}

    for (double t = knots[k - 1]; t <= knots[n + 1]; t += 0.01)
    {
        curvePoints.push_back(computeBSplinePoint(t, controlPointsQPoint, k));
    }

	return curvePoints;
}