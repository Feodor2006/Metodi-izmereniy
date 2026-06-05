set terminal windows 0 color solid butt enhanced standalone
set output
set title "Результаты отдельных наблюдений" font "Times-Roman, 24"
set xlabel "Номер измерения" font "Times-Roman, 20"
set ylabel "Напряжение, В" font "Times-Roman, 20"
set grid
set yrange [0.30:0.38]
set xrange [0:50]
plot "pack1.txt" with points pt 5 pointinterval 5
