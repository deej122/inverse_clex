import json
import matplotlib.pyplot as plt

json_data = open("plotting_data.json").read()

result = json.loads(json_data)

length = len(result["plotting_data"])

temperature = []
ensemble_average_absolute = []
ensemble_average_squared = []
ensemble_average_squares = []

for i in range(0, length):
	temperature.append(result["plotting_data"][i][0])
	ensemble_average_absolute.append(result["plotting_data"][i][1])
	ensemble_average_squared.append(result["plotting_data"][i][2])
	ensemble_average_squares.append(result["plotting_data"][i][3])
	x = result["plotting_data"][i][0]
	y1 = result["plotting_data"][i][1]
	y2 = result["plotting_data"][i][2]
	y3 = result["plotting_data"][i][3]
	plt.scatter(x, y1)
	plt.show()


print "T: ", temperature
print "Absolute Average: ", ensemble_average_absolute
print "Squared Average: ", ensemble_average_squared
print "Average of Squares: ", ensemble_average_squares