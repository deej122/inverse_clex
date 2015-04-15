import os
import shutil, errno
import sys
import pbs


# renames all the json files to be the same name as the directory it was in then makes a copy into a consolidated folder 'json_calcs'
rootDir = '../mc_raw_data'

dirs = []
for dir, subdir, filelist in os.walk(rootDir):
  for d in subdir:
    if( os.path.isdir(os.path.join(dir,d))): 
      dirs.append(os.path.join(dir,d))

filename_list = []

for path_name in dirs:
#print path_name
    #get last part of path
    print "path_name:", path_name
    filename = os.path.basename(path_name)
    print "filename:", filename
    filename_subset = filename.split("_")
    print filename_subset
    filename_list.append(filename)
    size = filename_subset[0]
    ECI_index = filename_subset[1]
    dim_index = filename_subset[2]
    temp_index = filename_subset[3]
    num_passes = 100
        
    print filename, size, ECI_index, dim_index, temp_index
        
    parent = os.getcwd()

    #run all the tests with the highest temp
    if temp_index == '11':
    #run the optimization
    #compare optimization if it's within a certian min squared mean then map
        directory = "highest_" + filename
        if not os.path.exists(directory):
            os.makedirs(directory)
        os.chdir(directory)
        #job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='python optimization.py ../' + filename)
        job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='../optimization.py ../' + filename)
        job.submit()
        os.chdir(parent)

    continue


    # runs all the tests with lowest temp
    if temp_index == '0':
    #run the optimization
        directory = "lowest_" + filename
        if not os.path.exists(directory):
            os.makedirs(directory)
        os.chdir(directory)
        job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='../optimization.py ../' + filename)
        job.submit()
        os.chdir(parent)
    #compare optimization if it's within a certian min squared mean then map



    # runs all the tests with transition temp
    if temp_index == '6':
    #run the optimization
        directory = "transition_" + filename
        if not os.path.exists(directory):
            os.makedirs(directory)
        os.chdir(directory)
        job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='../optimization.py ../' + filename)
        job.submit()
        os.chdir(parent)
    #compare optimization if it's within a certian min squared mean then map

    # runs all combinations of lowest and highest temp for same dim size and ECI
    if temp_index == '0':
        for filename2 in filename_list:
            filename2.split("_")
            size2 = filename[1]
            ECI_index2 = filename[2]
            dim_index2 = filename[3]
            temp_index2 = filename[4]
            num_passes2 = 100
            if temp_index2 == '11' and ECI_index == ECI_index2 and dim_index == dim_index2:
                #run the optimization
                directory = "low_" + filename1 + "high_" + filename2
                if not os.path.exists(directory):
                    os.makedirs(directory)
                os.chdir(directory)
                job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='../optimization.py ../' + filename + ' ../' + filename2)
                job.submit()
                os.chdir(parent)
                #compare the critical value

    # runs all combinations of lowest and transition temp for same dim size and ECI
    if temp_index == '0':
        for filename2 in filename_list:
            filename2.split("_")
            size2 = filename2[1]
            ECI_index2 = filename2[2]
            dim_index2 = filename2[3]
            temp_index2 = filename2[4]
            num_passes2 = 100
            if temp_index2 == '6' and ECI_index == ECI_index2 and dim_index == dim_index2:
                #run the optimization
                directory = "low_" + filename1 + "transition_" + filename2
                if not os.path.exists(directory):
                    os.makedirs(directory)
                os.chdir(directory)
                job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='../optimization.py ../' + filename + ' ../' + filename2)
                job.submit()
                os.chdir(parent)
                #compare the critical value



    # runs all combinations of highest and transition temp for same dim size and ECI
    if temp_index == '11':
        for filename2 in filename_list:
            filename2.split("_")
            size2 = filename2[1]
            ECI_index2 = filename2[2]
            dim_index2 = filename2[3]
            temp_index2 = filename2[4]
            num_passes2 = 100
            if temp_index2 == '6' and ECI_index == ECI_index2 and dim_index == dim_index2:
                #run the optimization
                directory = "high_" + filename1 + "transition_" + filename2
                if not os.path.exists(directory):
                        os.makedirs(directory)
                os.chdir(directory)
                job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='../optimization.py ../' + filename + ' ../' + filename2)
                job.submit()
                os.chdir(parent)
                #compare the critical value


    # runs all combinations of highest and transition temp
    if temp_index == '11':
        for filename2 in filename_list:
            filename2.split("_")
            size2 = filename2[1]
            ECI_index2 = filename2[2]
            dim_index2 = filename2[3]
            temp_index2 = filename2[4]
            num_passes2 = 100
            if temp_index2 == '6' and ECI_index == ECI_index2 and dim_index == dim_index2:
                for filename3 in filename_list:
                    filename3.split("_")
                    size3 = filename3[1]
                    ECI_index3 = filename3[2]
                    dim_index3 = filename3[3]
                    temp_index3 = filename3[4]
                    num_passes3 = 100
                    #run the optimization
                    if temp_index3 == '0' and ECI_index2 == ECI_index3 and dim_index3 == dim_index2:
                        directory = "high_" + filename + "transition_" + filename2 + "high_" + filename3
                        if not os.path.exists(directory):
                            os.makedirs(directory)
                        os.chdir(directory)
                        job = pbs.templates.NonPrismsJob(message = 1, ppn = '1', command='../optimization.py ../' + filename + ' ../' + filename2 + ' ../' + filename3)
                        job.submit()
                        os.chdir(parent)
                        #compare the critical value