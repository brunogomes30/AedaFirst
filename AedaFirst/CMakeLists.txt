cmake_minimum_required(VERSION 3.17)
project(AedaFirst)

set(CMAKE_CXX_STANDARD 14)

add_executable(AedaFirst main.cpp product.cpp product.h cake.cpp cake.h bread.cpp bread.h store.h store.cpp client.h client.cpp sale.h sale.cpp utilities.h utilities.cpp employee.h employee.cpp menu.h menu.cpp)
