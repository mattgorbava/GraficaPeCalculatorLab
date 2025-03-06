#pragma once

#define M_PI 3.14159265358979323846

#include <QPoint>

class CurvedLine
{
public:
	enum class Function
	{
		Undefined,
		Linear,
		Exponential,
		Logarithmic,
		Sine,
		Cosine,
		Tangent,
		Cotangent
	};

	struct Interval 
	{
		double start, end;
	};

	CurvedLine();

	CurvedLine(Function xFunction, Function yFunction, Interval interval);

	QPointF getPoint(double u);

private:
	Function xFunction;
	Function yFunction;
	Interval interval;
};