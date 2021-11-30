#Variables a usar
dataFile = "data1.txt"
titulo = "Tiempos de ejecución medidos"
xLabel = "Vértices"
yLabel = "Tiempo en milisegundos"

#Ajustes iniciales
set title titulo
set xlabel xLabel
set ylabel yLabel

#Mostrar los datos
plot dataFile with lines title "Kruskal", dataFile with points pointtype 7 title ""