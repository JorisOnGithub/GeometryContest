#!python3

import matplotlib.pyplot as plt
import matplotlib as mpl

def read_output(coord_filename,tour_filename):
	tour = []
	coordinates = []
	#if tour_filename=="euro_night15.ouput":
	#	print(tour_filename)
	#f = open("euro_night15.ouput",'r')
	#print(f.read())
	#f.close()
	#x = tour_filename
	#f2 = open(x,'r')
	#print(f2.read())
	with open(tour_filename,'r') as tour_file:
		start_reading = False
		for line in tour_file.readlines():
			if line[:len("TOUR_SECTION")] == "TOUR_SECTION":
				start_reading = True
				continue
			if not start_reading:
				continue
			if line[:len("EOF")] == "EOF" or int(line[:-1])==-1:
				break
			tour.append(int(line[:-1])-1)
	#print(tour)
	tour.append(0)
	with open(coord_filename, 'r') as coord_file:
		start_reading = False
		for line in coord_file.readlines():
			if line[:len("NODE_COORD_SECTION")] == "NODE_COORD_SECTION":
				start_reading = True
				continue
			if not start_reading:
				continue
			if line[:len("EDGE_WEIGHT_SECTION")] == "EDGE_WEIGHT_SECTION":
				break
			#print('>' + line)
			#print(line[:len("NODE_COORD_SECTION")])
			id,x,y = line[:-1].split()
			coordinates.append((int(id),int(x),int(y)))
	#print(coordinates)
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
	from sys import argv
	import os
	#f2 = open("euro_night15.ouput", 'r')
	#print(f2.read())
	#print(argv[1])	
	#print(argv[2])
	#print("euro_night15.output")
	#print(argv[2] == "euro_night15.output")
	#t = open("test.txt",'w')
	#t.write(argv[2])
	#f1 = open("euro_night15.output",'r')
	#f =  open("euro_night15.ouput",'r')
	#print(f1.read())
	#f1.close()
	#f2 = open(argv[2], 'r')
	#print(f2.read())
	#x = open("euro_night15.parea",'r')
	#print(x.read())
	#x.close()
	#print(os.getcwd())
	#print(os.listdir(os.getcwd()))
	#os.chdir(r'C:\Users\s134399\Documents\phd\Geom challenge polygon area\polygon-area-geometry-challenge\LKHWin-3.0.5')
	#print(os.listdir(os.getcwd()))
	#print(os.getcwd())
	#x = open('C:\\Users\\s134399\\Documents\\phd\\Geom challenge polygon area\\polygon-area-geometry-challenge\\LKHWin-3.0.5\\euro_night15.output')
	#x = open("euro_night15.output",'r')
	#print(x.read())
	if (len(argv) > 2):
		#coordinates,tour = read_output("euro_night15.parea","euro_night15.output")
		coordinates,tour = read_output(argv[1],argv[2])
		plot_points(coordinates,tour)
	elif (len(argv) > 1):
		coordinates,tour = read_output(argv[1] + ".parea",argv[1] + ".output")
		plot_points(coordinates,tour)