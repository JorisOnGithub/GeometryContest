To run LKH, a .par and a corresponding .parea file is required.
run " ./x64/Release/lkh.exe <name>.par " or "./x64/Release/lkh.exe" and enter the .par file manually.
Currently, only Max-area is supported and the negation of the area is reported. If lkh has found a solution of penalty 0, it will store the best such solution in a .output file.

The .par file contains all options for the solver, see DOC/LKH-3_PARAMETERS.pdf for details. The .parea file contains the actual instance data.

To generate a .parea file from a .instance file, run the python3 script "python preprocess_instance_LKH.py <name1>.instance <name2>.parea"

To plot a solution from an <name>.ouput file and a <name>.parea file (to find the coordinates of the vertices), run "python visualise_LKH_result.py <name>" or equivalently "python visualise_LKH_result.py <name>.parea <name>.output"
