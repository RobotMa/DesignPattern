add_executable(mainSingleton mainSingleton.cpp)
target_link_libraries(main CONAN_PKG::boost)

add_executable(Multiton Multiton.cpp)
#add_executable(singletonEnabledBydi BoostDi.cpp)

add_executable(SingletonTests SingletonTests.cpp)
target_link_libraries(SingletonTests CONAN_PKG::gtest
                                    CONAN_PKG::boost)