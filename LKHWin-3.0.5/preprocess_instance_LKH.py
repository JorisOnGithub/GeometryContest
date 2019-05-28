#!python3

def generate_file(infile_name):
	res = "NAME : " + infile_name + '\n' + "TYPE : PAREA\n"
	coordinates = []
	#id_length = len("Cities")
	#x_length = len("X_Coordinate")
	#y_length = len("Y_Coordinate")
	with open(infile_name, 'r') as infile:
		for line in infile.readlines():
			if line[0] == "#": 
				continue 
			(id, x, y) = line[:-1].split("\t")
			coordinates.append((id,x,y))
	N = len(coordinates)
	res += "DIMENSION : " + str(N) + '\n'
	res += "EDGE_WEIGHT_TYPE: EXPLICIT\nEDGE_WEIGHT_FORMAT: FULL_MATRIX\nNODE_COORD_TYPE : TWOD_COORDS\n"
	res += "NODE_COORD_SECTION\n"
	for i in range(N):
		res += str(int(coordinates[i][0])+1) + "\t" + str(coordinates[i][1]) + "\t" + str(coordinates[i][2]) + "\n"
	res += "EDGE_WEIGHT_SECTION\n"
	for i in range(N):
		line = ""
		for j in range(N):
			edge_cost = (int(coordinates[i][1]) * int(coordinates[j][2]) - int(coordinates[i][2]) * int(coordinates[j][1]) )/2
			line += str(round(edge_cost,1)) + " "
		res+=line[:-1] + '\n'	
	return res
	
 
if __name__ == "__main__":
	import sys
	infile_name = sys.argv[1]
	outfile_name = sys.argv[2]
	with open(outfile_name,'w') as outfile:
		outfile.write(generate_file(infile_name))