# Mínima versão do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(SearchStrategies)

# Especificar o padrão C++ (C++17 neste caso, mas pode ser ajustado)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Diretórios com os arquivos fonte
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Adicionar os executáveis
add_executable(main ${SRC_DIR}/main.cpp)
add_executable(test ${TEST_DIR}/testTime.cpp)

# Incluir diretórios para encontrar cabeçalhos (como strategyPattern.h)
target_include_directories(main PRIVATE ${SRC_DIR})
target_include_directories(test PRIVATE ${SRC_DIR})

# Se precisar de alguma biblioteca ou flags específicas, adicione aqui:
# Por exemplo:
# target_link_libraries(MainExecutable some_library)
# target_compile_options(TestExecutable PRIVATE -Wall -Wextra)
