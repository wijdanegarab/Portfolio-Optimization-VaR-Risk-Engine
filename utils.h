# pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

double mean(vector<double> v) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum / v.size();
}

double covariance(vector<double> v1, vector<double> v2, double mean1, double mean2) {
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += (v1[i] - mean1) * (v2[i] - mean2);
    }
    return sum / v1.size();
}

vector<vector<double>> cov_matrix(vector<vector<double>> returns) {
    int n = returns[0].size();
    int m = returns.size();
    vector<vector<double>> matrix(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<double> col_i(m);
            vector<double> col_j(m);
            for (int k = 0; k < m; k++) {
                col_i[k] = returns[k][i];
                col_j[k] = returns[k][j];
            }
            matrix[i][j] = covariance(col_i, col_j, mean(col_i), mean(col_j));
        }
    }
    return matrix;
}

