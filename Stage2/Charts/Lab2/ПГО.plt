set terminal windows 0 color solid butt enhanced standalone
set output
set title "Чувствительность горизонтальных пластин" font "Times-Roman, 20"
set xlabel "U_{eff}, В" font "Times-Roman, 20"
set ylabel "S_x, мм/В" font "Times-Roman, 20"
set grid
set yrange [0.7:1.1]
set xrange [3.1:23]
plot "pack2.txt" using 1:2:3 with yerrorbars , '' with points pt 7 title "S_x(U)"
