set terminal windows 0 color solid butt enhanced standalone
set output
set title "Чувствительность вертикальных пластин" font "Times-Roman, 20"
set xlabel "U_{eff}, В" font "Times-Roman, 20"
set ylabel "S_y, мм/В" font "Times-Roman, 20"
set grid
set yrange [0.9:1.4]
set xrange [2.1:18.1]
plot "pack1.txt" using 1:2:3 with yerrorbars , '' with points pt 7 title "S_y(U)"