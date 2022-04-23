add_executable(ChatRoom LiveChat.cpp Person.cpp)

add_executable(Soccer Soccer.cpp)
target_link_libraries(Soccer CONAN_PKG::boost)

add_executable(MediatorCodingExercise MediatorCodingExercise.cpp)
target_link_libraries(MediatorCodingExercise CONAN_PKG::gtest)