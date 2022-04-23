add_library(my_class MyClass.cpp)

add_executable(test_my_class TestMyClass.cpp)
target_link_libraries(test_my_class my_class)
