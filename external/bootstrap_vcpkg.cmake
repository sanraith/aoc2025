if (NOT EXISTS "${CMAKE_SOURCE_DIR}/external/vcpkg/vcpkg" AND NOT EXISTS "${CMAKE_SOURCE_DIR}/external/vcpkg/vcpkg.exe")
    message(STATUS "Bootstrapping vcpkg...")
    if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        set(BOOTSTRAP_COMMAND bootstrap-vcpkg.bat)
    else ()
        set(BOOTSTRAP_COMMAND ./bootstrap-vcpkg.sh)
    endif ()

    execute_process(
            COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/external/vcpkg ${BOOTSTRAP_COMMAND}
            RESULT_VARIABLE BOOTSTRAP_RESULT
    )

    if (NOT BOOTSTRAP_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to bootstrap vcpkg")
    endif ()
endif ()
