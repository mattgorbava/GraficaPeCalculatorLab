#pragma once

#define M_PI 3.14159265358979323846

#include <QPoint>

class CurvedLine
{
public:
	enum class Predefined 
	{
		Elipse,
		Spiral2D,
		XSquaredPlus1,
		Undefined
	};

	enum class Function
	{
		Linear,
		Quadratic,
		Exponential,
		Logarithmic,
		Sine,
		Cosine,
		Tangent,
		Cotangent,
		Undefined
	};

	struct Interval 
	{
		double start, end;
	};

	CurvedLine();

	CurvedLine(Predefined predefined);

	CurvedLine(Function xFunction, Function yFunction, Interval interval, double xCoefficient, double yCoefficient);

	QPointF getPoint(double u);

	Interval getInterval() const;

private:
	Function xFunction;
	Function yFunction;
	double xCoefficient;
	double yCoefficient;
	Interval interval;

	Predefined predefined;
};