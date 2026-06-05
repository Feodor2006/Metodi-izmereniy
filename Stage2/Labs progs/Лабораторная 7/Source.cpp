#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>

struct FitResult {
	double a, delta_a, b, delta_b;
	std::vector<std::vector<double>>table;
};

FitResult pairwise_fit(const std::vector<double>& x, const std::vector<double>& y) {
	size_t n = x.size();
	if (n % 2 != 0) throw std::runtime_error("Размер выборки должен быть чётным");
	size_t m = n / 2;
	std::vector<double>a_i(m);
	std::vector<std::vector<double>>table(m, std::vector<double>(8));

	for (size_t i = 0;i < m;++i) {
		size_t j = n - 1 - i;
		double dx = x[j] - x[i];
		double dy = y[j] - y[i];
		a_i[i] = dy / dx;
		table[i] = { double(i + 1),x[j],x[i],dx,y[j],y[i],dy,a_i[i] };
	}

	double sum_a = 0.0;
	for (double ai : a_i) sum_a += ai;
	double a_mean = sum_a / m;

	double sum_sq = 0.0;
	for (size_t i = 0;i < m;++i) {
		double diff = a_i[i] - a_mean;
		sum_sq += diff * diff;
		table[i].push_back(diff);
		table[i].push_back(diff* diff);
	}

	double S_a = std::sqrt(sum_sq / (m - 1));
	double S_a_mean = S_a / std::sqrt(m);
	double t_student = 2.365;//95% для m=8
	double delta_a = t_student * S_a_mean;

	double sum_x = 0.0, sum_y = 0.0;
	for (size_t i = 0;i < n;++i) { sum_x += x[i]; sum_y += y[i]; }
	double x_mean = sum_x / n;
	double y_mean = sum_y / n;
	double b = y_mean - a_mean * x_mean;

	double delta_b = delta_a * std::sqrt(sum_x * sum_x / n);

	return{ a_mean, delta_a,b,delta_b,table };
}