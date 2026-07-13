"""
simple_monte_carlo.py
和 C++/Boost 版对应的蒙特卡罗欧式看涨期权定价器。
  - 随机数：numpy 的 default_rng（PCG64），向量化一次抽 N 个正态
  - 对照解：用 math.erf 拼正态 CDF 算 Black-Scholes 闭式价
只依赖 numpy。运行: python simple_monte_carlo.py
"""

import math
import numpy as np


def monte_carlo_call(S0, K, r, vol, T, num_paths, rng=None):
    """欧式看涨的蒙特卡罗定价，返回 (价格, 标准误)。

    GBM 下直接抽终值 S_T，不逐步模拟路径。
    """
    if rng is None:
        rng = np.random.default_rng()

    drift = (r - 0.5 * vol * vol) * T
    diffusion = vol * math.sqrt(T)
    disc = math.exp(-r * T)

    # 向量化：一次抽 num_paths 个标准正态
    z = rng.standard_normal(num_paths)
    ST = S0 * np.exp(drift + diffusion * z)
    payoff = np.maximum(ST - K, 0.0)
    disc_payoff = disc * payoff

    price = disc_payoff.mean()
    # ddof=1 用样本方差；标准误 = 样本标准差 / sqrt(N)
    std_err = disc_payoff.std(ddof=1) / math.sqrt(num_paths)
    return price, std_err


def norm_cdf(x):
    """标准正态 CDF，用误差函数拼出来（免 scipy 依赖）。"""
    return 0.5 * (1.0 + math.erf(x / math.sqrt(2.0)))


def black_scholes_call(S0, K, r, vol, T):
    """Black-Scholes 闭式看涨价，做对照基准。"""
    sqrt_T = math.sqrt(T)
    d1 = (math.log(S0 / K) + (r + 0.5 * vol * vol) * T) / (vol * sqrt_T)
    d2 = d1 - vol * sqrt_T
    return S0 * norm_cdf(d1) - K * math.exp(-r * T) * norm_cdf(d2)


def main():
    # ---- 从键盘读入期权与市场参数 ----
    T = float(input("\nEnter expiry (T, in years): "))
    K = float(input("Enter strike (K): "))
    S0 = float(input("Enter spot (S0): "))
    vol = float(input("Enter vol (e.g. 0.20): "))
    r = float(input("Enter r (e.g. 0.05): "))
    num_paths = int(input("Enter number of paths: "))

    price, std_err = monte_carlo_call(S0, K, r, vol, T, num_paths)
    bs = black_scholes_call(S0, K, r, vol, T)

    print("\n--- Result ---")
    print(f"Paths                  : {num_paths}")
    print(f"Monte Carlo call price : {price:.4f}")
    print(f"Standard error         : {std_err:.4f}")
    print(f"95% CI                 : [{price - 1.96 * std_err:.4f}, "
          f"{price + 1.96 * std_err:.4f}]")
    print(f"Black-Scholes (exact)  : {bs:.4f}")
    print(f"MC - BS                : {price - bs:.4f}")


if __name__ == "__main__":
    main()
