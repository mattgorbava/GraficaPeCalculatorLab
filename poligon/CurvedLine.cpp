#include "CurvedLine.h"

CurvedLine::CurvedLine(Function xFunction, Function yFunction, Interval interval, double xCoefficient, double yCoefficient) :
	xFunction{ xFunction },
	yFunction{ yFunction },
	interval{ interval },
	xCoefficient{ xCoefficient },
	yCoefficient{ yCoefficient },
	predefined{ Predefined::Undefined }
{ }

CurvedLine::CurvedLine() :
	xFunction{ Function::Undefined },
	yFunction{ Function::Undefined },
	interval({ 0, 0 }),
	xCoefficient{ 0 },
	yCoefficient{ 0 },
	predefined{ Predefined::Undefined }
{ }

CurvedLine::CurvedLine(Predefined predefined)
	: predefined{ predefined }
{
	switch (predefined)
	{
	case Predefined::Elipse:
		interval = { 0, 2 };
		break;
	case Predefined::Spiral2D:
		interval = { 0, 20 };
		break;
	case Predefined::XSquaredPlus1:
		interval = { -2, 2 };
		break;
	}
}

QPointF CurvedLine::getPoint(double u)
{
	double x = 0, y = 0;

	if (predefined == Predefined::Undefined)
	{
		switch (xFunction)
		{
		case Function::Linear:
			x = interval.start + u * xCoefficient * (interval.end - interval.start);
			break;
		case Function::Quadratic:
			x = interval.start + xCoefficient * pow(u, 2) * (interval.end - interval.start);
			break;
		case Function::Exponential:
			x = interval.start * xCoefficient * pow(interval.end / interval.start, u);
			break;
		case Function::Logarithmic:
			x = interval.start + xCoefficient * log(u + 1) / log(interval.end + 1) * (interval.end - interval.start);
			break;
		case Function::Sine:
			x = interval.start + xCoefficient * sin(u * M_PI) * (interval.end - interval.start);
			break;
		case Function::Cosine:
			x = interval.start + xCoefficient * cos(u * M_PI) * (interval.end - interval.start);
			break;
		case Function::Tangent:
			x = interval.start + xCoefficient * tan(u * M_PI / 2) * (interval.end - interval.start);
			break;
		case Function::Cotangent:
			x = interval.start + xCoefficient * 1 / tan(u * M_PI / 2) * (interval.end - interval.start);
			break;
		}

		switch (yFunction)
		{
		case Function::Linear:
			y = interval.start + u * yCoefficient * (interval.end - interval.start);
			break;
		case Function::Quadratic:
			y = interval.start + yCoefficient * pow(u, 2) * (interval.end - interval.start);
			break;
		case Function::Exponential:
			y = interval.start * yCoefficient * pow(interval.end / interval.start, u);
			break;
		case Function::Logarithmic:
			y = interval.start + yCoefficient * log(u + 1) / log(interval.end + 1) * (interval.end - interval.start);
			break;
		case Function::Sine:
			y = interval.start + yCoefficient * sin(u * M_PI) * (interval.end - interval.start);
			break;
		case Function::Cosine:
			y = interval.start + yCoefficient * cos(u * M_PI) * (interval.end - interval.start);
			break;
		case Function::Tangent:
			y = interval.start + yCoefficient * tan(u * M_PI / 2) * (interval.end - interval.start);
			break;
		case Function::Cotangent:
			y = interval.start + yCoefficient * 1 / tan(u * M_PI / 2) * (interval.end - interval.start);
			break;
		}

	}
	else
	{
		switch (predefined)
		{
		case CurvedLine::Predefined::Elipse:
		{
			x = interval.start + cos(u * M_PI) * (interval.end - interval.start);
			y = interval.start + 2 * sin(u * M_PI) * (interval.end - interval.start);
			break;
		}
		case CurvedLine::Predefined::Spiral2D:
		{
			x = interval.start + u * cos(u) * (interval.end - interval.start);
			y = interval.start + u * sin(u) * (interval.end - interval.start);
			break;
		}
		case CurvedLine::Predefined::XSquaredPlus1:
		{
			x = interval.start + u * (interval.end - interval.start);
			y = interval.start + pow(x, 2) + 1;
			break;
		}
		default:
			break;
		}
	}

	return QPointF(x, y);
}

CurvedLine::Interval CurvedLine::getInterval() const
{
	return interval;
}