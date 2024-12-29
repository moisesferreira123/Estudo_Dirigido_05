# Configuração para tempo de execução para a busca com vetor desordenado

set title "Search algorithms Runtime (in sorted vector)" font ", 32"
set title offset 0,-0.95
set xlabel "Array size (number of elements)" font "helvetica, 24"
set xlabel offset 0,-1.8
set ylabel "Running time (in miliseconds)" font "helvetica, 24"
set ylabel offset +1.8,0

set style line 1 lc rgb 'red' dt 2 lt 1 lw 2
set style line 2 lc rgb 'blue' dt 2 lt 1 lw 2

set terminal png size 1920,1080
set o 'searchRuntimeSortedArray.png'

set grid               
set key top left         
set logscale y           
set xrange [0:300100]    
    
plot 'runtimeSortedArray.txt' u 1:2 title 'Linear search' w lp ls 1, \
     'runtimeSortedArray.txt' u 1:3 title 'Binary search' w lp ls 2

set out


# Configuração para tempo de execução para a busca com vetor desordenado

set title "Search algorithms Runtime (in unsorted vector)" font ", 32"
set title offset 0,-0.95
set xlabel "Array size (number of elements)" font "helvetica, 24"
set xlabel offset 0,-1.8
set ylabel "Running time (in miliseconds)" font "helvetica, 24"
set ylabel offset +1.8,0

set style line 1 lc rgb 'red' dt 2 lt 1 lw 2
set style line 2 lc rgb 'blue' dt 2 lt 1 lw 2

set terminal png size 1920,1080
set o 'searchRuntimeUnsortedArray.png'

set grid                 
set key top left         
set logscale y         
set xrange [0:300100]    
     
plot 'runtimeUnsortedArray.txt' u 1:2 title 'Linear search' w lp ls 1, \
     'runtimeUnsortedArray.txt' u 1:3 title 'Binary search' w lp ls 2

set out