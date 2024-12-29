#include <iostream>
#include "strategyPattern.h"
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

void usage(){
  std::cerr << "Uso:\n";
  std::cerr << "./main <caminho_do_arquivo_dos_codigos_do_inventario>\n";
  std::cerr << "Caso nenhum caminho de arquivo for passado, será considerado o caminho de arquivo padrão: 'vetor1.txt'\n";
}

int main(int argc, char* argv[]){

  std::string filePath; 
  if(argc == 1){
    filePath = "../docs/vetor1.txt";
  }else if(argc == 2){
    filePath = argv[1];
  }else{
    std::cerr << "ERRO: Foram passados muitos argumentos na entrada.\n";
    usage();
    exit(1);
  }

  std::ifstream input(filePath);
  std::vector<int> productCodesVector;
  int temp;
  // Lendo arquivo de entrada.
  while(input >> temp){
    productCodesVector.push_back(temp);
  }
  int productCodes[productCodesVector.size()];
  for(int i{0};i<productCodesVector.size();i++){
    productCodes[i] = productCodesVector[i];
  }
  int soughtCode;
  std::string strategy;
  bool isPositiveIntenger{false};
  std::string continueProgram{"s"};
  InventorySearchContext inventory(std::make_unique<LinearSearchStrategy>());
  while(continueProgram == "s"){
    while(!isPositiveIntenger){
      std::cout << "Digite o código do produto: ";
      if(std::cin >> soughtCode){
        if(soughtCode>0){
          isPositiveIntenger = true;
        }else{
          isPositiveIntenger = false;
          std::cout << "Entrada inválida! Digite um número positivo.\n";
        }
      }else{
        isPositiveIntenger = false;
        std::cout << "Entrada inválida! Digite um número inteiro positivo.\n";
      }
    }
    std:: cout << "\nDigite qual estratégia de busca desejas utilizar (digite b para binária ou l para linear): ";
    std::cin >> strategy;
    while(strategy != "b" and strategy != "l"){
      std::cout << "Entrada inválida! Digite b se quiseres busca binária ou l para busca linear: ";
      std::cin >> strategy;
    }
    if(strategy == "b"){
      std::cout << "Observação: Essa busca considera que o vetor está ordenado, então sempre garanta que o vetor está ordenado para realizar essa busca.\n";
      inventory.setStrategy(std::make_unique<BinarySearchStrategy>());
    }else if(strategy == "l"){
      inventory.setStrategy(std::make_unique<LinearSearchStrategy>());
    }
    int index = inventory.performSearch(productCodes, productCodesVector.size(), soughtCode);
    if(index == -1){
      std::cout << "Código do produto não está presente no inventário!\n";
    }else{
      std::cout << "Código do produto foi encontrado no inventário! Seu índice é " << index << ".\n";
    }
    std::cout << "Desejas continuar no programa (s/n): ";
    std::cin >> continueProgram;
    while(continueProgram != "s" and continueProgram != "n"){
      std::cout << "Resposta inválida! Digite s caso queira permanecer no programa ou n caso queira sair: ";
      std::cin >> continueProgram;
    }
    isPositiveIntenger = false;
  }

  return 0;
}