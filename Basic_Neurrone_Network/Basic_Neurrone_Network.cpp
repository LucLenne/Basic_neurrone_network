#include <iostream>
#include <cmath>
#include <array>
#include <random>
#include <Eigen/Dense>
#include <cstdlib>

class Pixel 
{
public:

	int RandomInt(int min, int max)
	{
		static std::random_device rd; 
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distrib(min, max);
		return distrib(gen);
	}

	Eigen::Vector3d RandomNotGreenPixel() 
	{
		int r = RandomInt(0, 200);
		int b = RandomInt(0, 200);

		int gMax = std::min(r + 55, b + 55);
		int g = RandomInt(0, gMax);

		return Eigen::Vector3d(r, g, b);
	}
};


class Perceptron
{
private:
	Pixel pixel;
	Eigen::Vector3d weights = Eigen::Vector3d::Random();;
	double learningRate;
	Eigen::Vector3d greenPixel = {0,255 ,0};


	double ScalarProduct(Eigen::Vector3d entry)
	{
		return entry.dot(weights);
	}

	bool ActivationFunction(double weightedSum)
	{
		return weightedSum > 0.5;
	} 

	void CalculateError() 
	{
		Eigen::Vector3d greenPixelNormalized = NormalizeValueVector(greenPixel);
		double error = 1 - ActivationFunction(ScalarProduct(greenPixelNormalized));
		weights += learningRate * error * greenPixelNormalized;
		//std::cout<<randomPixel;
	}

	Eigen::Vector3d NormalizeValueVector(Eigen::Vector3d VectorToNormalize)
	{
		return VectorToNormalize / 255;
	}


public:
	Perceptron(float pLearningRate)
	{
		learningRate = pLearningRate;
		greenPixel = NormalizeValueVector(greenPixel);
	}

	void TrainPerceptron(int numberIteration)
	{
		for (int i = 0; i < numberIteration; i++) 
		{
			CalculateError();
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
		return ActivationFunction(ScalarProduct(NormalizeValueVector(entry)));
	}
};


int main()
{
	srand(time(0));
	Perceptron perceptron(0.01f);
	perceptron.TrainPerceptron(100000);
	perceptron.PrintWeights();
	std::cout <<perceptron.Prediction({ 111,100,111 });
}

