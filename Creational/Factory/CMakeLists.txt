cmake_minimum_required (VERSION 3.18)
project(.)

set(CMAKE_CXX_STANDARD 20)

add_executable(Factory Factory.cpp)
add_executable(FactoryMethod FactoryMethod.cpp)
add_executable(InnerFactory InnerFactory.cpp)

add_subdirectory(AbstractFactory)
add_subdirectory(AbstractFactoryForClothes)
add_subdirectory(Utility)
add_subdirectory(Factory)