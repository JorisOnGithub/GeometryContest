import os
import subprocess
import argparse

parser = argparse.ArgumentParser(description="give me directory bitch")
parser.add_argument('--dir', required=True)
args = parser.parse_args()
directory = args.dir

for filename in os.listdir(directory):
    if not filename.endswith(".instance"):
        continue
    file_info = filename.split(".")
    points = int(file_info[0][-6:])
    if points <= 100:
        os.chdir("../")
        subprocess.check_call(["./Geometry_Contest", directory + filename])
