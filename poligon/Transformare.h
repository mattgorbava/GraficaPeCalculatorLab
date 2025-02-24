#pragma once

#include <QPoint>

class Transformare
{
public:
	struct Vector
	{
		double x, y, z;

		Vector(double x, double y, double z) : x(x), y(y), z(z) {}
	};

	struct Matrix
	{
		double a, b, c, d, e, f, g, h, i;

		Matrix(double a, double b, double c, double d, double e, double f, double g, double h, double i) :
			a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i) {}

		Matrix operator*(const Matrix& other)
		{
			return Matrix(
				a * other.a + b * other.d + c * other.g,
				a * other.b + b * other.e + c * other.h,
				a * other.c + b * other.f + c * other.i,
				d * other.a + e * other.d + f * other.g,
				d * other.b + e * other.e + f * other.h,
				d * other.c + e * other.f + f * other.i,
				g * other.a + h * other.d + i * other.g,
				g * other.b + h * other.e + i * other.h,
				g * other.c + h * other.f + i * other.i
			);
		}

		QPoint operator*(QPoint point)
		{
			return QPoint(
				a * point.x() + b * point.y() + c,
				d * point.x() + e * point.y() + f
			);
		}
	};

	static QPoint rotatePointAroundOrigin(QPoint point, double angle);
	static QPoint scalePointAroundOrigin(QPoint point, double scaleX, double scaleY);
	static QPoint translatePoint(QPoint point, int dx, int dy);
	static QPoint symmetricalPointByOrigin(QPoint point);

	static QPoint rotatePointAroundPoint(QPoint point, QPoint center, double angle);
	static QPoint scalePointAroundPoint(QPoint point, QPoint center, double scaleX, double scaleY);
	static QPoint symmetricalPointByEdge(QPoint point, QPoint edgePoint, Vector d);
};