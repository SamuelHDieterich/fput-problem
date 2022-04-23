# Reset previously sessions
reset

# Data input
file = "../data/output.dat"

# Statistics about the data
stats file name "A"

# Set range of plots
set xrange [A_min_x:A_max_x]    # x-axis
set yrange [-1.2:1.2]           # y-axis

# Customize the output 
set term pngcairo size 800, 550 background "#212121" enhanced font "Arial,10" fontscale 1.0

# Title and labels
set title "Título" font "Oswald,14" tc rgb "white"
set xlabel "Posição (x)" font ",10" tc rgb "white"
set ylabel "Altura (y)" font ",10" tc rgb "white"

# Tics and border
set tics tc rgb "white"
set border lc rgb "white"

# Total number of frames
tmax = int(A_blocks-1)

# Loop
do for [i=0:tmax] {  
    # Print: current_frame total_frame
    print i,tmax
    # Output file format
    outfile = sprintf("../img/fput%d.png", i)
    set output outfile
    # Plot
    plot file index i with points pt 7 ps 2
    }