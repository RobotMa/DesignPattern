add_executable(Observer ObserverDemo.cpp)
target_link_libraries(Observer CONAN_PKG::boost)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/capitals.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ObserverCodingExercise ObserverCodingExercise.cpp)
target_link_libraries(ObserverCodingExercise CONAN_PKG::gtest)