#include "portfolio.h"
#include "var.h"
#include <iostream>

using namespace std;


int main() {
    
    vector<vector<double>> returns = read_csv("returns.csv");

    
    vector<double> means;
    for (int i = 0; i < returns[0].size(); i++) {
        vector<double> col(returns.size());
        for (int j = 0; j < returns.size(); j++)
            col[j] = returns[j][i];
        means.push_back(mean(col) * 252);
    }
    vector<vector<double>> cov = cov_matrix(returns);
    for (int i = 0; i < cov.size(); i++){
        for (int j = 0; j < cov.size(); j++){
            cov[i][j] *= 252;

        }

    }
        


vector<double> best_weights = optimize_max_sharpe(means, cov);
ofstream f("weights.csv");
f << "AIR.PA,BNP.PA,OR.PA,SAN.PA,TTE.PA\n";
for (int i = 0; i < best_weights.size(); i++) {
    f << best_weights[i];
    if (i < best_weights.size() - 1) {
        f << ",";
    }
}
f << "\n";
    
    cout << "Rendement : " << portfolio_return(best_weights, means) << endl;
    cout << "Volatilite : " << portfolio_volatility(best_weights, cov) << endl;
    cout << "Sharpe : " << sharpe_ratio(best_weights, means, cov) << endl;

    
    vector<double> port_returns(returns.size());
    for (int i = 0; i < returns.size(); i++) {
        port_returns[i] = portfolio_return(best_weights, returns[i]);
    }

    
    cout << "VaR historique : " << historical_var(port_returns, 0.99) << endl;
    cout << "VaR parametrique : " << parametric_var(port_returns, 0.99) << endl;
    cout << "VaR Monte Carlo : " << monte_carlo_var(port_returns, 0.99) << endl;
    ofstream f2("port_returns.csv");
f2 << "returns\n";
for (int i = 0; i < port_returns.size(); i++) {
    f2 << port_returns[i] << "\n";
}

ofstream f3("var.csv");
f3 << "historical,parametric,montecarlo\n";
f3 << historical_var(port_returns, 0.99) << "," << parametric_var(port_returns, 0.99) << "," << monte_carlo_var(port_returns, 0.99) << "\n";

    
    save_frontier(means, cov);
ofstream f4("var95.csv");
f4 << "historical,parametric,montecarlo\n";
f4 << historical_var(port_returns, 0.95) << "," << parametric_var(port_returns, 0.95) << "," << monte_carlo_var(port_returns, 0.95) << "\n";

    return 0;
}
