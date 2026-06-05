# Настройки графика
set title "Зависимость lnI_{k} от U_{эб}" font "Times-Roman, 24"
set xlabel "U_{эб}, В" font "Times-Roman, 18"
set ylabel "lnI_{k}" font "Times-Roman, 18"
set grid

# Определение функции и аппроксимация
f(x) = a - x*b
fit f(x) "Pack1.txt" using 1:2 via a, b

# Построение графика
plot "Pack1.txt" using 1:2 with points pt 7 title "Исходные данные", \
     f(x) with lines lt 3 title "Аппроксимация: 3,274-31,09U"