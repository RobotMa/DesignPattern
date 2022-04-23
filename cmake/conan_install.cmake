option(CONAN_INSTALL "cmake will call conan install automatically" ON)

function(conan_install profile)
    set(CONAN_FILE ${CMAKE_SOURCE_DIR}/conanfile.py)

    foreach (option ${ARGN})
        set(CONAN_OPTIONS "${CONAN_OPTIONS} -o ${option}")
    endforeach ()

    message(STATUS "Installing conan dependencies with profile ${profile}")
    if (NOT EXISTS "conanbuildinfo.cmake")
        execute_process(
                COMMAND
                script /dev/null -e -q -f -c
                "conan install ${CMAKE_CURRENT_SOURCE_DIR} -if ${CMAKE_CURRENT_BINARY_DIR} --profile ${profile} ${CONAN_OPTIONS}"
                RESULT_VARIABLE CONAN_INSTALL_ERROR)
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/.conan_options" ${CONAN_OPTIONS})
    endif ()

    if (CONAN_INSTALL_ERROR)
        message(FATAL_ERROR "Conan installation failed")
    endif ()

    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CONAN_FILE})

endfunction()