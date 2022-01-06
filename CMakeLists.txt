cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_GOOGLE_TEST "Include google test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp)
add_library(ip_filter_lib ip_filter.cpp version.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(btest_ipfilter btest_ipfilter.cpp)

    set_target_properties(btest_ipfilter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(btest_ipfilter PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(btest_ipfilter
        ${Boost_LIBRARIES}
        ip_filter_lib
    )
endif()

if(WITH_GOOGLE_TEST)

    if (WIN32)
        set(GTEST_INCLUDE_DIR "C:/Program Files (x86)/googletest-distribution/include")
        set(GTEST_LIBRARY "C:/Program Files (x86)/googletest-distribution/lib/gtest.lib")
        set(GTEST_MAIN_LIBRARY "C:/Program Files (x86)/googletest-distribution/lib/gtest_main.lib")
    endif()
    
    find_package(GTest REQUIRED)
    add_executable(gtest_ipfilter gtest_ipfilter.cpp)

    set_target_properties(gtest_ipfilter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    include_directories(${GTEST_INCLUDE_DIR})

    target_link_libraries(gtest_ipfilter
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
        ip_filter_lib
    )

    if(UNIX)
        find_package(Threads REQUIRED)
        target_link_libraries(gtest_ipfilter
            pthread
        )
    endif()

endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(btest_ipfilter PRIVATE
            /W4
        )
    endif()
    if(WITH_GOOGLE_TEST)
        target_compile_options(gtest_ipfilter PRIVATE
            /MT
        )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(btest_ipfilter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

if (WIN32)
    set(CPACK_GENERATOR ZIP)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(btest_ipfilter btest_ipfilter)
endif()

if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(gtest_ipfilter gtest_ipfilter)
endif()