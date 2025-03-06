#include "CurvedLine.h"

CurvedLine::CurvedLine(Function xFunction, Function yFunction, Interval interval) :
	xFunction(xFunction),
	yFunction(yFunction),
	interval(interval)
{ }

QPointF CurvedLine::getPoint(double u)
{
	double x = 0, y = 0;

	switch (xFunction)
	{
	case Function::Linear:
		x = interval.start + u * (interval.end - interval.start);
		break;
	case Function::Exponential:
		x = interval.start * pow(interval.end / interval.start, u);
		break;
	case Function::Logarithmic:
		x = interval.start + log(u + 1) / log(interval.end + 1) * (interval.end - interval.start);
		break;
	case Function::Sine:
		x = interval.start + sin(u * M_PI) * (interval.end - interval.start);
		break;
	case Function::Cosine:
		x = interval.start + cos(u * M_PI) * (interval.end - interval.start);
		break;
	case Function::Tangent:
		x = interval.start + tan(u * M_PI / 2) * (interval.end - interval.start);
		break;
	case Function::Cotangent:
		x = interval.start + 1 / tan(u * M_PI / 2) * (interval.end - interval.start);
		break;
	}

	switch (yFunction)
	{
	case Function::Linear:
		y = interval.start + u * (interval.end - interval.start);
		break;
	case Function::Exponential:
		y = interval.start * pow(interval.end / interval.start, u);
		break;
	case Function::Logarithmic:
		y = interval.start + log(u + 1) / log(interval.end + 1) * (interval.end - interval.start);
		break;
	case Function::Sine:
		y = interval.start + sin(u * M_PI) * (interval.end - interval.start);
		break;
	case Function::Cosine:
		y = interval.start + cos(u * M_PI) * (interval.end - interval.start);
		break;
	case Function::Tangent:
		y = interval.start + tan(u * M_PI / 2) * (interval.end - interval.start);
		break;
	case Function::Cotangent:
		y = interval.start + 1 / tan(u * M_PI / 2) * (interval.end - interval.start);
		break;
	}

	return QPointF(x, y);
}