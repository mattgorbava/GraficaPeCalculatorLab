#include "Transformare.h"

#define PI 3.14159265358979323846 

QPointF Transformare::rotatePointAroundOrigin(QPointF point, double angle)
{
	double radians = angle * PI / 180.0;
	double sinA = sin(radians);
	double cosA = cos(radians);
	Matrix rotationMatrix(cosA, -sinA, 0, sinA, cosA, 0, 0, 0, 1);
	return rotationMatrix * point;
}

QPointF Transformare::scalePointAroundOrigin(QPointF point, double scaleX, double scaleY)
{
	Matrix scaleMatrix(scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
	return scaleMatrix * point;
}

QPointF Transformare::translatePoint(QPointF point, int dx, int dy)
{
	Matrix translationMatrix(1, 0, dx, 0, 1, dy, 0, 0, 1);
	return translationMatrix * point;
}

QPointF Transformare::symmetricalPointByOrigin(QPointF point)
{
	Matrix symmetricalMatrix(-1, 0, 0, 0, -1, 0, 0, 0, 1);
	return symmetricalMatrix * point;
}

QPointF Transformare::rotatePointAroundPoint(QPointF point, QPointF center, double angle)
{
	return translatePoint(rotatePointAroundOrigin(translatePoint(point, -center.x(), -center.y()), angle), center.x(), center.y());
}

QPointF Transformare::scalePointAroundPoint(QPointF point, QPointF center, double scaleX, double scaleY)
{
	return translatePoint(scalePointAroundOrigin(translatePoint(point, -center.x(), -center.y()), scaleX, scaleY), center.x(), center.y());
}