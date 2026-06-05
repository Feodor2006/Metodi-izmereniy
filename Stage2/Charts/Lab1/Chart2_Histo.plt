#!/usr/bin/gnuplot

set terminal pngcairo size 1200,900 enhanced font "Times Roman,16"
set output "Chart2.png"

set title "Распределение результатов измерений" font "Times Roman, 24"
set xlabel "Значение (В)" font "Times Roman,16"
set ylabel "Частота" font "Times Roman,16"
set grid y
set key off

# Данные: середина интервала, частота
$hist << EOD
0.36025 4
0.36075 5
0.36125 2
0.36175 5
0.36225 14
0.36275 17
0.36325 3
EOD

# Ширина интервала
interval_width = 0.0005

set boxwidth interval_width absolute
set style fill solid 0.7 border -1

set xrange [0.3600 : 0.3635]
set yrange [0:17]

set xtics rotate by 45 right font "Times Roman,12"
set xtics ("0,3600" 0.3600, \
           "0,3605" 0.3605, \
           "0,361" 0.3610, \
           "0,3615" 0.3615, \
           "0,362" 0.3620, \
           "0,3625" 0.3625, \
           "0,363" 0.363, \
           "0,3635" 0.3635)

plot $hist using 1:2 with boxes lc rgb "steelblue" notitle

print "Гистограмма сохранена: Chart2.png"
