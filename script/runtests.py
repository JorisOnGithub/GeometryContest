import os
import subprocess
import argparse

parser = argparse.ArgumentParser(description="give me directory bitch")
parser.add_argument('--dir', required=True)
args = parser.parse_args()
directory = args.dir

os.chdir("..")
print(subprocess.check_output(["pwd"]))
for filename in os.listdir(directory):
    if not filename.endswith(".instance"):
        continue
#    file_info = filename.split(".")
    uniform_info = filename.split("m-")
    points = int(uniform_info[1][:7])
#    points = int(file_info[0][-7:])
    if points <= 500:
        subprocess.check_call(["./cmake-build-debug/Geometry_Contest", directory + filename])
