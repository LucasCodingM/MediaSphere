
cmake_minimum_required(VERSION 3.16)
project(appMediaSphereTest LANGUAGES CXX)
# Find the required Qt6 modules for testing
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Test Quick Multimedia LinguistTools QuickControls2)

qt_standard_project_setup()

# Include directories for testing (same as the src folder)
include_directories(${CMAKE_SOURCE_DIR}/../src)

# Add test files
qt_add_executable(appMediaSphereTest
    ${CMAKE_SOURCE_DIR}/../src/weather/openmeteoapi.h
    ${CMAKE_SOURCE_DIR}/../src/weather/openmeteoapi.cpp
    test_openmeteoapi.cpp
    test_openmeteoapi.h
    mocknetworkreply.h
    mocknetworkreply.cpp
)

qt_add_resources(appMediaSphereTest "json"
    FILES
    forecast.json
    infoIp.json)

set_target_properties(appMediaSphereTest PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Link the test executable with necessary libraries
target_link_libraries(appMediaSphereTest PRIVATE
    Qt6::Quick
    Qt6::Multimedia
    Qt6::Core
    Qt6::QuickControls2
    Qt6::Test)

install(TARGETS appMediaSphereTest
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET appMediaSphereTest
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
