#!python3
"""
Script to plot solutions given in contest format. Requires matplotlib.

USAGE

"python visualise_solution <instance_file> <solution_file>" : plots the solution in <solution_file> of instance in <instance_file> .

"python visualise_solution <solution_file>" : plots the solution in 'solutions/<solution_file>' of the instance in 'instances' with the matching filename


"""

import matplotlib.pyplot as plt
import matplotlib as mpl

def read_files(instance_file, solution_file):
	coordinates = []
	with open(instance_file, 'r') as instance:
		for line in instance:
			if line[0] == "#": 
				continue 
			(id, x, y) = line[:-1].split("\t")
			try:
				coordinates.append((int(id),int(x),int(y)))
			except ValueError:
				#silently ignore invalid lines
				continue
	tour = []
	first = -1
	with open(solution_file,'r') as solution:
		start_reading = False
		for line in solution:
			if line[0] == "#":
				continue
			try:
				number = int(line[:-1])
			except ValueError:
				#silently ignore invalid lines
				continue
			if first == -1:
				first = number
			tour.append(number)
	tour.append(first)
	return (coordinates,tour)



def plot_points(coordinates,tour):
	fig,ax = plt.subplots()
	x = [coordinates[tour[i]][1] for i in range(len(tour))]
	y = [coordinates[tour[i]][2] for i in range(len(tour))]
	id = [coordinates[tour[i]][0] for i in range(len(tour))]
	line, = ax.plot(x,y, 'g.-')
	ax.grid()
	for i in range(len(tour)-1):
		ax.annotate(id[i], (x[i],y[i]))
	plt.show()
 
if __name__ == "__main__":
	import sys
	if len(sys.argv) > 2:
		coordinates,tour = read_files(sys.argv[1],sys.argv[2])
		plot_points(coordinates,tour)
	elif len(sys.argv) > 1:
		solution_path = 'solutions/' + sys.argv[1]
		instance_filename = sys.argv[1].split(".")[0] + ".instance"
		instance_path = 'instances/' + instance_filename
		coordinates,tour = read_files(instance_path, solution_path)
		plot_points(coordinates,tour)
	else:
		print("No file specified")