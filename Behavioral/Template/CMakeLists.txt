add_executable(TemplateMethod TemplateMethod.cpp)

add_executable(TemplateMethodCodingExercise TemplateMethodCodingExercise.cpp)
target_link_libraries(TemplateMethodCodingExercise CONAN_PKG::gtest)