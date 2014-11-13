import json

json_data=open("monte_carlo_calcs.json").read()

result = json.loads(json_data)

print result["Data_by_pass"][0]["num_species"]
