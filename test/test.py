import json

json_data=open("monte_carlo_calcs.json").read()

result = json.loads(json_data)
num_pass = len(result["Data_by_pass"]) - 1
#need to change this if more than 2 species
avg_spin = abs(result["Data_by_pass"][num_pass]["num_species"][0]*result["Species"][0] + result["Data_by_pass"][num_pass]["num_species"][1]*result["Species"][1])/num_pass

print avg_spin

#result["Data_by_pass"][100]["num_species"]
