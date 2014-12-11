import json
import matplotlib.pyplot as plt
import time

mc_data = json.loads(open('monte_carlo_calcs.json').read())
color = ['r', 'b']
a=[]
fig = plt.figure()

plt.show(block=False)

for p in mc_data["Data_by_pass"]:
	x = []
	y = []
	s = []
	for site in p["sites"]:
		x.append(site["coord"][0])
		y.append(site["coord"][1])
		s.append(site["curr_occupant"])
	a.append(plt.scatter(x, y, c=s, s=100, linewidths=0.0))
	plt.gca().set_xlim([-1, max(x)+1])
	plt.gca().set_ylim([-1, max(y)+1])
	plt.draw()
	print "here1"
	time.sleep(0.01)
	print "here2"
	#a[-1].set_visible(False)

