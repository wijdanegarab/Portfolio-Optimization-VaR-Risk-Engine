#pragma once
#include "utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

vector<vector<double>> read_csv(string name) {
    vector<vector<double>> returns;
    ifstream file(name);
    string line, token;

    getline(file, line); // ignore l'en-tête

    while (getline(file, line)) {
        stringstream ss(line);
        vector<double> row;
        while (getline(ss, token, ','))
            row.push_back(stod(token));
        returns.push_back(row);
    }
    return returns;
}

double portfolio_return(vector<double> weights, vector<double> means) {
    double sum = 0;
    for (int i = 0; i < weights.size(); i++) {
        sum += weights[i] * means[i];
    }
    return sum;
}

double portfolio_volatility(vector<double> weights, vector<vector<double>> cov) {
    double sum = 0;
    for (int i = 0; i < weights.size(); i++) {
        for (int j = 0; j < weights.size(); j++) {
            sum += weights[i] * weights[j] * cov[i][j];
        }
    }
    return sqrt(sum);
}

double sharpe_ratio(vector<double> weights, vector<double> means, vector<vector<double>> cov) {
    return (portfolio_return(weights, means) - 0.03) / portfolio_volatility(weights, cov);
}

vector<double> random_weights(int n) {
    vector<double> weights(n);
    double sum = 0;
    for (int i = 0; i < n; i++) {
        weights[i] = rand();
        sum += weights[i];
    }
    for (int i = 0; i < n; i++) {
        weights[i] /= sum;
    }
    return weights;
}

vector<double> optimize_max_sharpe(vector<double> means, vector<vector<double>> cov) {
    int n = means.size();
    vector<double> best_weights = random_weights(n);
    double best_sharpe = sharpe_ratio(best_weights, means, cov);

    for (int i = 0; i < 10000; i++) {
        vector<double> weights = random_weights(n);
        double s = sharpe_ratio(weights, means, cov);
        if (s > best_sharpe) {
            best_sharpe = s;
            best_weights = weights;
        }
    }
    return best_weights;
}


vector<double> optimize_min_variance(vector<double> means, vector<vector<double>> cov) {
    int n = means.size();
    vector<double> best_weights = random_weights(n);
    double best_vol = portfolio_volatility(best_weights, cov);

    for (int i = 0; i < 10000; i++) {
        vector<double> weights = random_weights(n);
        double v = portfolio_volatility(weights, cov);
        if (v < best_vol) {
            best_vol = v;
            best_weights = weights;
        }
    }
    return best_weights;
}

void save_frontier(vector<double> means, vector<vector<double>> cov) {
    ofstream file("frontier.csv");
    file << "volatility,return\n";
    for (int i = 0; i < 10000; i++) {
        vector<double> weights = random_weights(means.size());
        file << portfolio_volatility(weights, cov) << "," << portfolio_return(weights, means) << "\n";
    }
}
