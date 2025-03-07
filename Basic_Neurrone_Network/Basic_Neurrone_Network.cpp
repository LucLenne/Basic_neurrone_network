#include <iostream>
#include <cmath>
#include <array>
//#include <Eigen>
//#include <Eigen/Dense>


class Perceptron
{
private:
	std::array<double, 3> weights = { 0.1 , 0.1 , 0.1 };
	std::array<double, 3> entryMatrix;

	double VariableMultiplication()
	{
		return weights[0] * entryMatrix[0] + weights[1] * entryMatrix[1] + weights[2] * entryMatrix[2];
	}

	bool ActivationFunction(double weightedSum)
	{
		return weightedSum > 100;
	}

public:
	Perceptron(std::array<double, 3> entry)
	{
		entryMatrix = entry;
	}

	void Predict()
	{
		std::cout << ActivationFunction(VariableMultiplication());
	}
};


int main()
{
	Perceptron bGreen({ 0.1,0.5,0.9 });
	bGreen.Predict();
}

