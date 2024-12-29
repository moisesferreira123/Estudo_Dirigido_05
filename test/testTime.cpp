#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include <algorithm>
#include "../src/strategyPattern.h"

#define NON_EXISTING_CODE -1
#define MAX_SIZE_VECTOR 300050
#define SPACE_BETWEEN_ARRAYS 5000
#define SMALL_SIZE 50
#define MEDIUM_SIZE 5000
#define BIG_SIZE 100000

void createArray(int array[], int size){
  for(int num{0};num<size;num++){
    array[num] = num+1;
  }
}

std::chrono::duration<double,std::milli>  runTimeSearch(int productCodes[], int size, std::string search){
  InventorySearchContext inventory(std::make_unique<LinearSearchStrategy>());
  if(search == "Linear"){
    inventory.setStrategy(std::make_unique<LinearSearchStrategy>());
  }else if(search == "Binaria"){
    inventory.setStrategy(std::make_unique<BinarySearchStrategy>());
  }
  auto begin = std::chrono::high_resolution_clock::now();
  inventory.performSearch(productCodes, size, NON_EXISTING_CODE);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double,std::milli> duration = end-begin;
  return duration;
}

// Vai ser utilizado para gerar um gráfico com informações sobre diferentes tamanhos de vetores ordenados no gnuplot
void sortedArrayData(){
  int arraySize = SMALL_SIZE;
  int array[MAX_SIZE_VECTOR];
  int number{0};
  std::chrono::duration<double, std::milli> durationLinear, durationBinary;
  std::ofstream output("../docs/runtimeSortedArray.txt");
  if(!output){
    std::cerr << "Erro ao abrir arquivo de registro!\n";
    exit(1);
  }
  output << "# Linear search time vs Binary search time (in sorted array and in milliseconds)\n";
  output << "# Array size        Linear          Binary\n";
  while(arraySize <= MAX_SIZE_VECTOR){
    array[number] = number+1;
    number++;
    if(number == arraySize){
      durationLinear = runTimeSearch(array, arraySize, "Linear");
      durationBinary = runTimeSearch(array, arraySize, "Binaria");
      output << arraySize << "        " << durationLinear.count() << "        " << durationBinary.count() << "\n";
      arraySize += SPACE_BETWEEN_ARRAYS;
    }
  }
  output.close();
}

// Vai ser utilizado para gerar um gráfico com informações sobre diferentes tamanhos de vetores desordenados no gnuplot
void unsortedArrayData(){
  int arraySize = SMALL_SIZE;
  int array[MAX_SIZE_VECTOR];
  int number{0};
  std::chrono::duration<double, std::milli> durationLinear, durationBinary;
  std::ofstream output("../docs/runtimeUnsortedArray.txt");
  if(!output){
    std::cerr << "Erro ao abrir arquivo de registro!\n";
    exit(1);
  }
  output << "# Linear search time vs Binary search time (in unsorted array and in milliseconds)\n";
  output << "# Array size        Linear          Binary\n";
  while(arraySize <= MAX_SIZE_VECTOR){
    array[number] = number+1;
    number++;
    if(number == arraySize){
      // Embaralhando o vetor.
      std::random_device rd;  
      std::mt19937 gen(rd()); 
      std::shuffle(array, array+arraySize, gen);
      
      durationLinear = runTimeSearch(array, arraySize, "Linear");
      // Calculando o tempo de execução para ordenar o vetor
      auto begin = std::chrono::high_resolution_clock::now();
      std::sort(array, array+arraySize);
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double,std::milli> durationSort = end-begin;
      durationBinary = runTimeSearch(array, arraySize, "Binaria");
      output << arraySize << "        " << durationLinear.count() << "        " << durationSort.count() + durationBinary.count() << "\n";
      arraySize += SPACE_BETWEEN_ARRAYS;
    }
  }
  output.close();
}

int main(){

  std::ofstream loggerArchive("../docs/logger.txt", std::ios::app);
  if(!loggerArchive){
    std::cerr << "Erro ao abrir arquivo de registro!\n";
    exit(1);
  }
  loggerArchive << "Iniciando um novo registro!\n";
  int smallArray[SMALL_SIZE];
  createArray(smallArray, SMALL_SIZE);
  int mediumArray[MEDIUM_SIZE];
  createArray(mediumArray, MEDIUM_SIZE);
  int bigArray[BIG_SIZE];
  createArray(bigArray, BIG_SIZE);
  std::chrono::duration<double,std::milli> duration;

  std::cout << "Executando as buscas em array pequeno (50 elementos)\n";
  loggerArchive << "Executando as buscas em array pequeno (50 elementos)\n";
  // Tempo de execução da busca linear em array pequeno:
  std::cout << "Executando algoritmo da busca linear ...\n";
  loggerArchive << "Executando algoritmo da busca linear ...\n";
  duration = runTimeSearch(smallArray, SMALL_SIZE, "Linear");
  std::cout << "Tempo de execução da busca linear: " << duration.count() << " milliseconds.\n";
  loggerArchive << "Tempo de execução da busca linear: " << duration.count() << " milliseconds.\n";
  // ---
  // Tempo de execução da busca binária em array pequeno:
  std::cout << "Executando algoritmo da busca binária ...\n";
  loggerArchive << "Executando algoritmo da busca binária ...\n";
  duration = runTimeSearch(smallArray, SMALL_SIZE, "Binaria");
  std::cout << "Tempo de execução da busca binária: " << duration.count() << " milliseconds.\n";
  loggerArchive << "Tempo de execução da busca binária: " << duration.count() << " milliseconds.\n";
  // ---

  std::cout << "Executando as buscas em array médio (5000 elementos)\n";
  loggerArchive << "Executando as buscas em array médio (5000 elementos)\n";;
  // Tempo de execução da busca linear em array médio:
  std::cout << "Executando algoritmo da busca linear ...\n";
  loggerArchive << "Executando algoritmo da busca linear ...\n";
  duration = runTimeSearch(mediumArray, MEDIUM_SIZE, "Linear");
  std::cout << "Tempo de execução da busca linear: " << duration.count() << " milliseconds.\n";
  loggerArchive << "Tempo de execução da busca linear: " << duration.count() << " milliseconds.\n";
  // ---
  // Tempo de execução da busca binária em array médio:
  std::cout << "Executando algoritmo da busca binária ...\n";
  loggerArchive << "Executando algoritmo da busca binária ...\n";
  duration = runTimeSearch(mediumArray, MEDIUM_SIZE, "Binaria");
  std::cout << "Tempo de execução da busca binária: " << duration.count() << " milliseconds.\n";
  loggerArchive << "Tempo de execução da busca binária: " << duration.count() << " milliseconds.\n";
  // ---

  std::cout << "Executando as buscas em array grande (100000 elementos)\n";
  loggerArchive << "Executando as buscas em array grande (100000 elementos)\n";
  // Tempo de execução da busca linear em array grande:
  std::cout << "Executando algoritmo da busca linear ...\n";
  loggerArchive << "Executando algoritmo da busca linear ...\n";
  duration = runTimeSearch(bigArray, BIG_SIZE, "Linear");
  std::cout << "Tempo de execução da busca linear: " << duration.count() << " milliseconds.\n";
  loggerArchive << "Tempo de execução da busca linear: " << duration.count() << " milliseconds.\n";
  // ---
  // Tempo de execução da busca binária em array grande:
  std::cout << "Executando algoritmo da busca binária ...\n";
  loggerArchive << "Executando algoritmo da busca binária ...\n";
  duration = runTimeSearch(bigArray, BIG_SIZE, "Binaria");
  std::cout << "Tempo de execução da busca binária: " << duration.count() << " milliseconds.\n";
  loggerArchive << "Tempo de execução da busca binária: " << duration.count() << " milliseconds.\n";
  // ---

  loggerArchive.close();

  sortedArrayData();
  unsortedArrayData();

 return 0;
}