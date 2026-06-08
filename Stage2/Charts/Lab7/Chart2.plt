# Настройки графика
set title "Зависимость I_{k} от U_{эб}" font "Times-Roman, 24"
set xlabel "U_{эб}, В" font "Times-Roman, 18"
set ylabel "I_{k}, мА" font "Times-Roman, 18"
set grid

# Определение функции и аппроксимация
f(x) = a - x*b
fit f(x) "Pack2.txt" using 1:2 via a, b

# Построение графика
plot "Pack2.txt" using 1:2 with points pt 7 title "Исходные данные", \
     f(x) with lines lt 3 title "Аппроксимация: I_{k}=I_{0}e^{eU/kT}"