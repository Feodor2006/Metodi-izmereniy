#!/usr/bin/gnuplot

set terminal pngcairo size 1200,900 enhanced font "Times Roman,16"
set output "Chart3.png"

set title "Полигон частот распределения результатов измерений" font "Times Roman, 24"
set xlabel "Значение (В)" font "Times Roman,16"
set ylabel "Частота" font "Times Roman,16"
set grid
set key off

$polygon << EOD
0.36025 4
0.36075 5
0.36125 2
0.36175 5
0.36225 14
0.36275 17
0.36325 3
EOD

set xrange [0.3600 : 0.3635]
set yrange [0:20]

set xtics rotate by 45 right font "Times Roman,12"
set xtics ("0,3600" 0.3600, \
           "0,3605" 0.3605, \
           "0,361" 0.3610, \
           "0,3615" 0.3615, \
           "0,362" 0.3620, \
           "0,3625" 0.3625, \
           "0,363" 0.363, \
           "0,3635" 0.3635)

plot $polygon using 1:2 smooth csplines with lines lw 2 lc rgb "red", \
     $polygon using 1:2 with points pt 7 ps 1.5 lc rgb "red"

print "Полигон частот сохранён: Chart3.png"
