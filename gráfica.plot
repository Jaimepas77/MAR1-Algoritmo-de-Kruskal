#Ajustes iniciales
set title "Tiempos de ejecución medidos"
set xlabel "Vértices"
set ylabel "Tiempo en milisegundos"

#Mostrar los datos
plot "data1.txt" with lines title "Kruskal", "data1.txt" with points pointtype 7 title ""