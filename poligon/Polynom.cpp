#include "Polynom.h"

Polynom::Polynom(Polygon& polygon)
{
	computeCoefficients(polygon);
}

Polynom::~Polynom()
{ }

double Polynom::computeValue(double x)
{
	double result = 0;
	for (int i = 0; i < coefficients.size(); i++)
	{
		result += coefficients[i] * pow(x, i);
	}
	return result;
}

void Polynom::computeCoefficients(Polygon& polygon)
{
	std::vector<Node*> nodes = polygon.getNodes();
	std::vector<std::vector<double>> matrix(nodes.size(), std::vector<double>(nodes.size(), 0.0));

	for (int i = 0; i < nodes.size(); i++)
	{
		matrix[i][i] = nodes[i]->getCoordY();
	}

	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		for (int j = i + 1; j < nodes.size(); j++)
		{
			matrix[i][j] = (matrix[i + 1][j] - matrix[i][j - 1]) / (nodes[j]->getCoordX() - nodes[i]->getCoordX());
		}
	}
}