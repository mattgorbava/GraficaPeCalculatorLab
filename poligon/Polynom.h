#pragma once

#include <vector>
#include "polygon.h"

class Polynom
{
public:
	Polynom() { }
	Polynom(Polygon& polygon);
	~Polynom();

	double computeValue(double x);
	std::vector<double> getCoefficients() { return coefficients; }

private:
	void computeCoefficients(Polygon& polygon);
	std::vector<double> coefficients;
};