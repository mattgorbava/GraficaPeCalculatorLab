#pragma once

#include <vector>
#include "polygon.h"

class Polynom
{
public:
	Polynom() { }
	//Polynom(std::vector<Node*> nodes);
	~Polynom();

	double computeValueNewton(double x, std::vector<Node*> nodes);
	double computeValueLagrange(double x, std::vector<Node*> nodes);
	std::vector<double> getCoefficients() { return coefficients; }
	void computeCoefficientsNewton(std::vector<Node*> nodes);
	void computeCoefficientsLagrange(std::vector<Node*> nodes);

private:
	std::vector<double> coefficients;
};