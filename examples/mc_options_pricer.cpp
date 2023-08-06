#include <iostream>
#include <future>
#include <random>
#include <cmath>
#include <chrono>
#include <vector>

std::random_device rd;
std::mt19937_64 gen(rd());
std::normal_distribution<double> distribution(0.0, 1.0);

double generate_final_option_price(double initial_price, double rate, double volatility, int time_steps) {
    double dt = 1.0 / time_steps;
    double res = initial_price;
    for (int i = 0; i < time_steps; i++) {
        double arg_one = (rate - (volatility * volatility) / 2) * dt;
        double arg_two = volatility * std::sqrt(dt) * distribution(gen);
        res = res * std::exp(arg_one + arg_two);
    }

    return std::max(0.0, res - initial_price);
}

int main () {
    double initial_strike = 5.0;
    double rate = 0.05;
    double volatility = 0.03;
    int time_steps = 1000;
    int num_samples = 1000;

    std::cout << "Initial Strike: " << initial_strike << std::endl;

    std::vector<std::future<double>> option_prices;

    for (int i = 0; i < num_samples; i++) {
        option_prices.push_back(std::async(generate_final_option_price, initial_strike, rate, volatility, time_steps));
    }

    double expected_option_price = 0.0;
    for (int i = 0; i < num_samples; i++) {
        expected_option_price += option_prices[i].get();
    }

    expected_option_price /= num_samples;
    std::cout << "Expected option price using 1000 samples with " << time_steps << " time steps: " << expected_option_price << std::endl;

    return 0;
}