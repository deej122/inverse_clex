import os
import shutil, errno
import sys
import pbs
import os
import json

rootDir = '../mc_raw_data'

dirs = []
for dir, subdir, filelist in os.walk(rootDir):
  for d in subdir:
    if( os.path.isdir(os.path.join(dir,d))): 
      dirs.append(os.path.join(dir,d))

for path_name in dirs:
	#get list of all the directories
	filename = os.path.basename(path_name)
	if (filename == "optimization_results.json"):
		json_optimization_results = open("optimization_results.json").read()
		optimization_results = json.loads(json_optimization_results)
		with open("compiled_optimization.json") as feeds_json:
			feeds.append(optimization_results)
			json.dump(feeds, feeds_json)