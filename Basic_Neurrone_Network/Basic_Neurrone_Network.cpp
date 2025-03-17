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
	Eigen::Vector3d greenPixel = {0,255 ,0};


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

	void ResetWeights()
	{
		for (int i = 0; i < 2; i++) {
			weights[i] = 0,1;
		}
	}

	void PrintWeights()
	{
		std::cout << "w1 : " + std::to_string(weights[0]) << std::endl;
		std::cout << "w2 : " + std::to_string(weights[1]) << std::endl;
		std::cout << "w3 : " + std::to_string(weights[2]) << std::endl;
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
	perceptron.PrintWeights();
	std::cout << perceptron.Prediction({ 0,255,0 });
}

