import pandas as pd
import matplotlib.pyplot as plt

frontier = pd.read_csv("frontier.csv")
plt.scatter(frontier["volatility"], frontier["return"], s=1)
plt.xlabel("Volatilité")
plt.ylabel("Rendement")
plt.title("Frontière efficiente")
plt.show()


weights = pd.read_csv("weights.csv")
tickers = ["AIR.PA", "BNP.PA", "OR.PA", "SAN.PA", "TTE.PA"]
values = weights.iloc[0].values
plt.pie(values, labels=tickers, autopct='%1.1f%%')
plt.title("Poids du portefeuille optimal")
plt.show()


port_returns = pd.read_csv("port_returns.csv")
var = pd.read_csv("var.csv")

plt.hist(port_returns["returns"], bins=50)
plt.axvline(var["historical"][0], color='r', label="VaR historique")
plt.axvline(var["parametric"][0], color='g', label="VaR paramétrique")
plt.axvline(var["montecarlo"][0], color='b', label="VaR Monte Carlo")
plt.legend()
plt.title("Distribution des rendements et VaR")
plt.show()

var95 = pd.read_csv("var95.csv")

methods = ["Historique", "Parametrique", "Monte Carlo"]
values99 = [var["historical"][0], var["parametric"][0], var["montecarlo"][0]]
values95 = [var95["historical"][0], var95["parametric"][0], var95["montecarlo"][0]]

x = [0, 1, 2]
plt.bar([i - 0.2 for i in x], values99, width=0.4, label="99%")
plt.bar([i + 0.2 for i in x], values95, width=0.4, label="95%")
plt.xticks(x, methods)
plt.legend()
plt.title("Comparaison VaR 95% et 99%")
plt.show()
