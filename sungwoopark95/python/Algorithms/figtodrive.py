import matplotlib.pyplot as plt
import numpy as np

PATH = "/Users/sungwoo/ppatteori109@gmail.com - Google Drive/내 드라이브/GSDS/ohlab/Research/latent-context/figures"
x = sorted(np.random.randint(1, 100, size=30))
y = [item**2 for item in x]

fig = plt.figure(figsize=(8, 5))
plt.plot(x, y)
plt.grid(True)
plt.savefig(f"{PATH}/fig.png")
