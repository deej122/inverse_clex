import json
import matplotlib
import numpy as np
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from lnQ import calc_ln_Q

# json_mc_data_10 = open("monte_carlo_calcs_10.json").read()
# json_mc_data_100 = open("monte_carlo_calcs_100.json").read()
# json_mc_data_1000 = open("monte_carlo_calcs_1000.json").read()
# json_mc_data_10000 = open("monte_carlo_calcs_10000.json").read()
json_mc_data_30000 = open("monte_carlo_calcs_30000.json").read()
# json_mc_data_100000 = open("monte_carlo_calcs_100000.json").read()
# json_mc_data_200000 = open("monte_carlo_calcs_200000.json").read()
# json_mc_data_300000 = open("monte_carlo_calcs_300000.json").read()
#add temperatures > 30000K
# mc_data_10 = json.loads(json_mc_data_10)
# mc_data_100 = json.loads(json_mc_data_100)
# mc_data_1000 = json.loads(json_mc_data_1000)
# mc_data_10000 = json.loads(json_mc_data_10000)
mc_data_30000 = json.loads(json_mc_data_30000)
# mc_data_100000 = json.loads(json_mc_data_100000)
# mc_data_200000 = json.loads(json_mc_data_200000)
# mc_data_300000 = json.loads(json_mc_data_300000)

mc_data = [mc_data_30000]

delta = .05

x = np.arange(0.5, 1.5, delta)
y = np.arange(-1.0, 1.0, delta)

X, Y = np.meshgrid(x,y)
Z = np.zeros(np.shape(X))

for i in range(np.shape(X)[0]):
	for j in range(np.shape(X)[1]):
		ECI = [X[i, j], 0, Y[i, j]]
		print ECI
		Z[i, j] = calc_ln_Q(ECI, mc_data)
		# json.dump("contour_data.json")

# 2D contour plot
plt.figure()
contour = plt.contour(X, Y, Z, 20)
plt.show()

# 3D surface plot
fig = plt.figure()
ax = fig.gca(projection='3d')
surface = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.coolwarm,
        linewidth=0, antialiased=False)
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
fig.colorbar(surface, shrink=0.5, aspect=5)
plt.show()

