cmake_minimum_required(VERSION 3.16)
project(cutiefeedback VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick DBus)
qt_standard_project_setup()

set(lib_SOURCES
    src/cutiefeedback.h
    src/cutiefeedback.cpp)

qt6_add_library(cutiefeedback
    SHARED ${lib_SOURCES}
)

set_target_properties(cutiefeedback PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cutiefeedback PROPERTIES SOVERSION 0)
set_target_properties(cutiefeedback PROPERTIES PUBLIC_HEADER src/cutiefeedback.h)

target_link_libraries(cutiefeedback PUBLIC
    Qt::Core
    Qt::Quick
    Qt::DBus
)

configure_file(src/cutiefeedback.pc.in cutiefeedback.pc @ONLY)

install(TARGETS cutiefeedback
    RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    BUNDLE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(FILES ${CMAKE_BINARY_DIR}/cutiefeedback.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
