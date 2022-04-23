#add_executable(Iterator Iterator.cpp)

add_executable(IteratorFacade Iterator-Facade.cpp)
target_link_libraries(IteratorFacade CONAN_PKG::boost)

add_executable(IteratorCodingExercise Iterator-Coding-Exercise.cpp)
target_link_libraries(IteratorCodingExercise CONAN_PKG::gtest)
