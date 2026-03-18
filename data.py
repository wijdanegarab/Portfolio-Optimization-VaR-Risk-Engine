import yfinance as yf

tickers = ["TTE.PA", "BNP.PA", "AIR.PA", "OR.PA", "SAN.PA"]
data = yf.download(tickers, start="2020-01-01", end="2024-01-01")["Close"]
data.pct_change().dropna().to_csv("returns.csv", index=False)
