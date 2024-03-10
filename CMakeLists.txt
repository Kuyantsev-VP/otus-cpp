cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

# option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_GTEST "Whether to build GTest" ON)

# configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp)
add_library(ip_address ip_address.cpp)
add_library(utils utils.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_address
    utils
)


# if(WITH_GTEST)
#     add_executable(test_version_gtest test_version_gtest.cpp)

#     include(FetchContent)
#         FetchContent_Declare(
#         googletest
#         URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#     )
#     # For Windows: Prevent overriding the parent project's compiler/linker settings
#     set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#     FetchContent_MakeAvailable(googletest)

#     target_link_libraries(
#         test_version_gtest
#         GTest::gtest_main
#         helloworld
#     )
#     include(GoogleTest)
# endif()

target_compile_options(ip_filter PRIVATE
    -Wall -Wextra -pedantic
)
target_compile_options(ip_address PRIVATE
    -Wall -Wextra -pedantic
)
target_compile_options(utils PRIVATE
    -Wall -Wextra -pedantic
)
# if(WITH_GTEST)
#     target_compile_options(test_version_gtest PRIVATE
#         -Wall -Wextra -pedantic -Werror
#     )
# endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


# if(WITH_GTEST)
#     enable_testing()
#     gtest_discover_tests(test_version_gtest)
# endif()