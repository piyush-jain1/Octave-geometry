# Octave-geometry

Union of two polygons implemented using Clipper Polygon library.
----------------------------------------------------------------

Clone and unzip the repository.
polyUnion.oct file has been made already.

To make oct file on your own :<br>
Run the following command in the respective dirtectory :<br>
`mkoctfile clipper.cpp polyUnion.cc -o polyUnion`

#### Input format : 
Input is taken in the form of cells.<br>
First cell represents the set of x coordinates of each of the subject polygons.<br>
Second cell represents the set of y coordinates of each of the subject polygons.<br>

Take a test input in octave, for e.g. x = {[0 100 100 0],[50 150 150 50]} , y = {[0 0 100 100],[0 0 100 100]}<br>
Call function : polyUnion(x,y)

Function will return the vertices of Union of the two subject polygons.
