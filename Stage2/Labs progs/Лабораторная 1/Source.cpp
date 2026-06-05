#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
	std::vector<double> values;
	std::ifstream file("Pack2.txt");

	if (!file) {
		std::cerr << "Не удалось открыть файл!" << std::endl;
		return 1;
	}

	int number;
	double value;
	while (file >> number >> value) {
		values.push_back(value);
	}
	file.close();

	int n = values.size();

	//Вычисление среднего
	double sum = 0;
	for (double v : values) sum += v;
	double mean = sum / n;

	//Вычисление суммы квадратов отклонений
	double sum_sq_diff = 0;
	for (double v : values) {
		double diff = v - mean;
		sum_sq_diff += diff * diff;
	}

	//Вычисление СКО и погрешности среднего
	double sigma = sqrt(sum_sq_diff / (n - 1));
	double sigma_tau = sigma / sqrt(n);

	std::cout << std::fixed << std::setprecision(6);
	std::cout << "Результаты обработки:" << std::endl;
	std::cout << "n = " << n << std::endl;
	std::cout << "x = " << mean << " B" << std::endl;
	std::cout << "sigma = " << sigma << " B" << std::endl;
	std::cout << "delta_x = " << sigma_tau << " B" << std::endl;

	return 0;
}