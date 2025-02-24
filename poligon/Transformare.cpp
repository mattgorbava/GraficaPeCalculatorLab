#include "Transformare.h"

#define PI 3.14159265358979323846 

QPoint Transformare::rotatePointAroundOrigin(QPoint point, double angle)
{
	double radians = angle * PI / 180.0;
	double sinA = sin(radians);
	double cosA = cos(radians);
	Matrix rotationMatrix(cosA, -sinA, 0, sinA, cosA, 0, 0, 0, 1);
	return rotationMatrix * point;
}

QPoint Transformare::scalePointAroundOrigin(QPoint point, double scaleX, double scaleY)
{
	Matrix scaleMatrix(scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
	return scaleMatrix * point;
}

QPoint Transformare::translatePoint(QPoint point, int dx, int dy)
{
	Matrix translationMatrix(1, 0, dx, 0, 1, dy, 0, 0, 1);
	return translationMatrix * point;
}

QPoint Transformare::symmetricalPointByOrigin(QPoint point)
{
	Matrix symmetricalMatrix(-1, 0, 0, 0, -1, 0, 0, 0, 1);
	return symmetricalMatrix * point;
}

QPoint Transformare::rotatePointAroundPoint(QPoint point, QPoint center, double angle)
{
	return translatePoint(rotatePointAroundOrigin(translatePoint(point, -center.x(), -center.y()), angle), center.x(), center.y());
}

QPoint Transformare::scalePointAroundPoint(QPoint point, QPoint center, double scaleX, double scaleY)
{
	return translatePoint(scalePointAroundOrigin(translatePoint(point, -center.x(), -center.y()), scaleX, scaleY), center.x(), center.y());
}