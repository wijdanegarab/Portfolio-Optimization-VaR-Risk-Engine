#pragma once
#include "utils.h"
#include <algorithm>
#include <random>

using namespace std;

double historical_var(vector<double> returns, double confidence) {
    sort(returns.begin(), returns.end());
    int index = (1 - confidence) * returns.size();
    return returns[index];
}

double parametric_var(vector<double> returns, double confidence) {
    double m = mean(returns);
    double variance = 0;
    for (int i = 0; i < returns.size(); i++) {
        variance += (returns[i] - m) * (returns[i] - m);
    }
    double std = sqrt(variance / returns.size());
    double z = -2.326; // z-score pour 99%
    return m + z * std;
}

double monte_carlo_var(vector<double> returns, double confidence) {
    double m = mean(returns);
    double variance = 0;
    for (int i = 0; i < returns.size(); i++) {
        variance += (returns[i] - m) * (returns[i] - m);
    }
    double std = sqrt(variance / returns.size());

    normal_distribution<double> dist(m, std);
    default_random_engine generator;
    vector<double> simulations(10000);
    for (int i = 0; i < 10000; i++) {
        simulations[i] = dist(generator);
    }
    sort(simulations.begin(), simulations.end());
    return simulations[(1 - confidence) * 10000];
}
