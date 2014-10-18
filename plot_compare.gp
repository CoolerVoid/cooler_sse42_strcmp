reset
dx=5.
n=2
total_box_width_relative=0.75
gap_width_relative=0.1
d_width=(gap_width_relative+total_box_width_relative)*dx/2.
reset
set term png truecolor
set output "profit.png"
set grid
set border linecolor rgbcolor "cyan"
set key textcolor rgbcolor "yellow"
set title "Coolerudo's Benchmark strcmp() vs sse4.2 strcmp()" textcolor rgbcolor "cyan"
set ylabel "CPU cycles" textcolor rgbcolor "yellow"
set xlabel "Cyan - simple strcmp()\nGreen - SSE4.2 strcmp()" textcolor rgbcolor "yellow"
set obj 1 rectangle behind from screen 0,0 to screen 1,1
set obj 1 fillstyle solid 1.0 fillcolor rgbcolor "black"
set boxwidth total_box_width_relative/n relative
set style fill transparent solid 0.5 noborder
plot "bench.dat" u 1:2 w boxes lc rgb"green" notitle,\
     "bench.dat" u ($1+d_width):3 w boxes lc rgb"cyan" notitle
