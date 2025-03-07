#include <iostream>
#include <cmath>
#include <array>
#include <Eigen/Dense>
#include <cstdlib>

class Pixel 
{
public:
	Eigen::Vector3d RandomPixel() 
	{
		srand(time(0));
		return Eigen::Vector3d(rand() % 256, rand() % 256, rand() % 256);
	}
	bool IsGreen(Eigen::Vector3d pixel)
	{

	}
};


class Perceptron
{
private:
	Eigen::Vector3d entryMatrix;
	Eigen::Vector3d weights = {0.1,0.1,0.1};


	double ScalarProduct()
	{
		return entryMatrix.dot(weights);
	}

	bool ActivationFunction(double weightedSum)
	{
		return weightedSum > 100;
	}

public:
	Perceptron(Eigen::Vector3d entry)
	{
		entryMatrix = entry;
	}

	void Predict()
	{
		std::cout << ActivationFunction(ScalarProduct());
	}
};


int main()
{
	Perceptron bGreen({ 0.1,0.5,0.9 });
	bGreen.Predict();
	Pixel pixel;
	pixel.RandomPixel();
}

