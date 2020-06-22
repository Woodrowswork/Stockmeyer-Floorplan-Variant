# Stockmeyer-Floorplan-Variant

This C++ code accepts as input from command line an equation in polish notation presenting the floorplan of a potential IC. Then it executes a variant of the stockmeyer algorithm detailed here http://limsk.ece.gatech.edu/book/slides/pdf/stockmeyer.pdf in order to reduce the over foot print of the IC modules. My variant on the algorithm is much more efficient than the original. 

Original footprint 15 x 12 = 180
Stockmeyer solution 13 x 9 = 117
Variant 25 x 3 = 75

Both the stockmeyer algorithm and my variant fail to take wiring the floorplan into account which may prove difficult depending on the critical path. 
