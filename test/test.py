import json

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


print "T: ", temperature
print "Absolute Average: ", ensemble_average_absolute
print "Squared Average: ", ensemble_average_squared
print "Average of Squares: ", ensemble_average_squares