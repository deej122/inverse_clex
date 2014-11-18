import json
import matplotlib.pyplot as plot_ensemble_avg_abs
import matplotlib.pyplot as plot_ensemble_avg_squared
import matplotlib.pyplot as plot_ensemble_avg_squares



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

fig_ensemble_avg_abs = plot_ensemble_avg_abs.figure()
fig_ensemble_avg_squared = plot_ensemble_avg_squared.figure()
fig_ensemble_avg_squares = plot_ensemble_avg_squares.figure()

plot1 = fig_ensemble_avg_abs.add_subplot(111)
plot1.set_title('Ensemble Average Absolute Value vs Temp')
plot1.set_xlabel('temperature (K)')
plot1.set_ylabel('Ensemble Average Absolute Value')
plot1.plot(temperature, ensemble_average_absolute, 'o')

plot2 = fig_ensemble_avg_squared.add_subplot(111)
plot2.set_title('Ensemble Average Squared vs Temp')
plot2.set_xlabel('temperature (K)')
plot2.set_ylabel('Ensemble Average Squared')
plot2.plot(temperature, ensemble_average_squared, 'o')

plot3 = fig_ensemble_avg_squares.add_subplot(111)
plot3.set_title('Ensemble Average Squares vs Temp')
plot3.set_xlabel('temperature (K)')
plot3.set_ylabel('Ensemble Average Squares')
plot3.plot(temperature, ensemble_average_squares, 'o')

plot_ensemble_avg_abs.show()
plot_ensemble_avg_squared()
plot_ensemble_avg_squares()

print "T: ", temperature
print "Absolute Average: ", ensemble_average_absolute
print "Squared Average: ", ensemble_average_squared
print "Average of Squares: ", ensemble_average_squares