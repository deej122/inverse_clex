import json
import matplotlib.pyplot as plot_ensemble_avg_abs
import matplotlib.pyplot as plot_ensemble_avg_squared
import matplotlib.pyplot as plot_ensemble_avg_squares

input_file_name = ["plotting_data_10.json", "plotting_data_100.json", "plotting_data_1000.json"]
color = ["r", "b", "g"]

fig_ensemble_avg_abs = plot_ensemble_avg_abs.figure()
fig_ensemble_avg_squared = plot_ensemble_avg_squared.figure()
fig_ensemble_avg_squares = plot_ensemble_avg_squares.figure()

plot1 = fig_ensemble_avg_abs.add_subplot(111)
plot1.set_title('Ensemble Average Absolute Value vs Temp')
plot1.set_xlabel('temperature (K)')
plot1.set_xscale('log')
plot1.set_ylabel('Ensemble Average Absolute Value')

plot2 = fig_ensemble_avg_squared.add_subplot(111)
plot2.set_title('Ensemble Average Squared vs Temp')
plot2.set_xlabel('temperature (K)')
plot2.set_xscale('log')
plot2.set_ylabel('Ensemble Average Squared')
#plot2.ylim([0,1.2])

plot3 = fig_ensemble_avg_squares.add_subplot(111)
plot3.set_title('Ensemble Average Squares vs Temp')
plot3.set_xlabel('temperature (K)')
plot3.set_xscale('log')
plot3.set_ylabel('Ensemble Average Squares')
#plot3.ylim([0,1.2])

for index in range(3):

	json_data = open(input_file_name[index]).read()

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



	plot1.plot(temperature, ensemble_average_absolute, 'o-', c=color[index])
	plot2.plot(temperature, ensemble_average_squared, 'o-', c=color[index])
	plot3.plot(temperature, ensemble_average_squares, 'o-', c=color[index])


plot1.set_ylim([0,1.2])
plot2.set_ylim([0,1.2])
plot3.set_ylim([0,1.2])

plot_ensemble_avg_abs.show()
plot_ensemble_avg_squared()
plot_ensemble_avg_squares()





print "T: ", temperature
print "Absolute Average: ", ensemble_average_absolute
print "Squared Average: ", ensemble_average_squared
print "Average of Squares: ", ensemble_average_squares