add_executable(Proxy Proxy.cpp)
target_link_libraries(Proxy CONAN_PKG::cpprestsdk)

add_executable(ProxyCodingExercise ProxyCodingExercise.cpp)
target_link_libraries(ProxyCodingExercise CONAN_PKG::gtest)
