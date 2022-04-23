project(SOLID)

add_executable(SRP Creational-SRP.cpp)
target_link_libraries(SRP CONAN_PKG::boost)

add_executable(OCP Creational-OCP.cpp)
add_executable(LSP Creational-LSP.cpp)
add_executable(ISP Creational-ISP.cpp)
add_executable(DIP Creational-DIP.cpp)