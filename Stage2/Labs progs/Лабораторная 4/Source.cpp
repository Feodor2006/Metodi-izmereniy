#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <numeric>

constexpr double H = 0.272;
constexpr double DELTA_H = 0.001;
constexpr double V0 = 1.050;
constexpr double DELTA_V0 = 1.050;
constexpr double DIAMETER = 0.01;
constexpr double PI = 3.141592653589793;
constexpr double VOLUME = PI * DIAMETER * DIAMETER * DIAMETER / 6.0;
constexpr double INSTRUMENT_ERROR_MS = 0.5;
constexpr double T_COEFF = 2.04523;

struct MaterialResult {
	std::string name;
	double density;
	double mass;
	std::vector<double> times_ms;
	double mean_t_ms;
	double total_error_t_ms;
	double g;
	double delta_g;
};

double mean(const std::vector<double>& v) {
	if (v.empty()) return 0.0;
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double stdev(const std::vector<double>& v, double mean_val) {
	if (v.size() <= 1) return 0.0;
	double sq_sum = 0.0;
	for (double x : v)
		sq_sum += (x - mean_val) * (x - mean_val);
	return std::sqrt(sq_sum / (v.size() - 1));
}

int main() {
	std::ifstream infile("data.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: cannot open data.txt\n";
	}

	std::vector<MaterialResult> materials(6);
	materials[0] = { "Aluminum", 2790.0, 2790.0 * VOLUME, {} };
	materials[1] = { "Brass", 8500.0, 8500.0 * VOLUME, {} };
	materials[2] = { "Steel", 7900.0, 7900.0 * VOLUME, {} };
	materials[3] = { "Wood", 700.0, 700.0 * VOLUME, {} };
	materials[4] = { "Plexiglas", 1180.0, 1180.0 * VOLUME, {} };
	materials[5] = { "Lead", 11340.0, 11340.0 * VOLUME, {} };

	std::string line;
	while (std::getline(infile, line)) {
		size_t dot_pos = line.find('.');
		if (dot_pos != std::string::npos)
			line = line.substr(dot_pos + 1);
		std::istringstream iss(line);
		double val;
		int col = 0;
		while (iss >> val && col < 6)
			materials[col++].times_ms.push_back(val);
	}
	infile.close();

	//Обработка и ввод результатов
	for (auto& mat : materials) {
		size_t n = mat.times_ms.size();

		double mean_t = mean(mat.times_ms);
		double std_t = stdev(mat.times_ms, mean_t);
		double std_mean_t = std_t / std::sqrt(n);
		double random_err = T_COEFF * std_mean_t;
		double total_err = std::sqrt(random_err * random_err
			+ INSTRUMENT_ERROR_MS * INSTRUMENT_ERROR_MS);
		double t_sec = mean_t / 1000.0;
		double dt_sec = total_err / 1000.0;
		double denom = H - V0 * t_sec;
		double g_val = 2.0 * denom / (t_sec * t_sec);
		double dg = g_val * std::sqrt(
			std::pow(DELTA_H / denom, 2) +
			std::pow((V0 + g_val * t_sec) * dt_sec / denom, 2) +
			std::pow(t_sec * DELTA_V0 / denom, 2)
		);

		mat.mean_t_ms = mean_t;
		mat.total_error_t_ms = total_err;
		mat.g = g_val;
		mat.delta_g = dg;

		std::cout << mat.name << ": <t>=" << mean_t
			<< " ms, dt=" << total_err << " ms, g="
			<< g_val << " m/s^2, dg=" << dg << "\n";
	}

	return 0;
}