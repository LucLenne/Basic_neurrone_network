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
};


class Perceptron
{
private:
	Pixel pixel;
	Eigen::Vector3d entryMatrix;
	Eigen::Vector3d weights = {0.1,0.1,0.1};
	double learningRate;
	Eigen::Vector3d greenPixel;


	double ScalarProduct(Eigen::Vector3d entry)
	{
		return entry.dot(weights);
	}

	bool ActivationFunction(double weightedSum)
	{
		return weightedSum > 0.8;
	}

	void CalculateError() 
	{
		double error = ScalarProduct(greenPixel) - ScalarProduct(entryMatrix);
		for (int i = 0 ; i < 3 ; i++) 
		{
			weights[i] += learningRate * error * entryMatrix[i];
			std::cout << weights[i] << std::endl;
		}
		entryMatrix = NormalizeValueVector(pixel.RandomPixel());
	}

	Eigen::Vector3d NormalizeValueVector(Eigen::Vector3d vectorToNormalize)
	{
		return vectorToNormalize / 255;
	}

public:
	Perceptron(float pLearningRate)
	{
		learningRate = pLearningRate;
		greenPixel = NormalizeValueVector({ 0,255,0 });
	}

	void TrainPerceptron(int numberIteration)
	{
		for (int i = 0; i < numberIteration; i++) 
		{
			CalculateError();
		}
	}

	Eigen::Vector3d PrintWeights()
	{
		return weights;
	}

	bool Prediction(Eigen::Vector3d entry) 
	{
		return ActivationFunction(ScalarProduct(entry));
	}
};


int main()
{
	Perceptron perceptron(0.01f);
	perceptron.TrainPerceptron(100);
	std::cout << perceptron.PrintWeights() << std::endl;
	std::cout << perceptron.Prediction({ 0,255,0 });
}

