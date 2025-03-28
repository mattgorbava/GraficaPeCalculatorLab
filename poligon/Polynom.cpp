#include "Polynom.h"

//Polynom::Polynom(std::vector<Node*> nodes)
//{
//	computeCoefficients(nodes);
//}

Polynom::~Polynom()
{ }

double Polynom::computeValueNewton(double x, std::vector<Node*> nodes)
{
	double result = coefficients[0];
	double term = 1.0;

	for (int i = 1; i < coefficients.size(); i++)
	{
		term *= (x - nodes[i - 1]->getCoordX());
		result += coefficients[i] * term;
	}

	return result;
}

double Polynom::computeValueLagrange(double x, std::vector<Node*> nodes)
{
	double result = 0.0;

	for (int i = 0; i < nodes.size(); ++i) 
	{
		double term = nodes[i]->getCoordY();
		double L_i = 1.0;

		for (int j = 0; j < nodes.size(); ++j) {
			if (j != i) {
				L_i *= (x - nodes[j]->getCoordX()) / (nodes[i]->getCoordX() - nodes[j]->getCoordX());
			}
		}

		result += term * L_i;
	}

	return result;
}

void Polynom::computeCoefficientsNewton(std::vector<Node*> nodes)
{
	std::vector<std::vector<double>> matrix(nodes.size(), std::vector<double>(nodes.size(), 0.0));

	for (int i = 0; i < nodes.size(); ++i)
	{
		matrix[i][i] = nodes[i]->getCoordY();
	}

	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		for (int j = i + 1; j < nodes.size(); ++j)
		{
			matrix[i][j] = 
				(matrix[i + 1][j] - matrix[i][j - 1]) / 
				(nodes[j]->getCoordX() - nodes[i]->getCoordX());
		}
	}

	coefficients.clear();

	for (int i = 0; i < nodes.size(); ++i)
	{
		coefficients.push_back(matrix[0][i]);
	}
}

void Polynom::computeCoefficientsLagrange(std::vector<Node*> nodes)
{
	coefficients.clear();
	coefficients.resize(nodes.size(), 0.0);

	for (int i = 0; i < nodes.size(); ++i)
	{
		double y_i = nodes[i]->getCoordY();

		std::vector<double> Li_coefficients(nodes.size(), 0.0);
		Li_coefficients[0] = 1.0;

		double x_i = nodes[i]->getCoordX();

		for (int j = 0; j < nodes.size(); ++j)
		{
			if (i != j)
			{
				double x_j = nodes[j]->getCoordX();
				double factor = 1.0 / (x_i - x_j);

				std::vector<double> temp = Li_coefficients;

				for (int k = nodes.size() - 1; k > 0; --k)
				{
					Li_coefficients[k] = temp[k - 1] * factor;
				}
				Li_coefficients[0] = 0.0;

				for (int k = 0; k < nodes.size(); ++k)
				{
					Li_coefficients[k] -= x_j * temp[k] * factor;
				}
			}

		}
		for (int j = 0; j < nodes.size(); ++j)
		{
			coefficients[j] += y_i * Li_coefficients[j];
		}
	}
}