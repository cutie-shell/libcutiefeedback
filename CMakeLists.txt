cmake_minimum_required(VERSION 3.16)
project(cutiefeedback VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick DBus)
qt_standard_project_setup()

set(lib_SOURCES
    src/cutiefeedback.h
    src/cutiefeedback.cpp)

set(plugin_SOURCES
    src/plugin.cpp src/plugin.h)

qt6_add_library(cutiefeedback
    SHARED ${lib_SOURCES}
)

qt6_add_qml_module(qmlcutiefeedbackplugin
    URI Cutie.Feedback
    VERSION ${PROJECT_VERSION}
    PLUGIN_TARGET qmlcutiefeedbackplugin
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${plugin_SOURCES}
)

set_target_properties(cutiefeedback PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cutiefeedback PROPERTIES SOVERSION 0)
set_target_properties(cutiefeedback PROPERTIES PUBLIC_HEADER src/cutiefeedback.h)

target_link_libraries(cutiefeedback PUBLIC
    Qt::Core
    Qt::Quick
    Qt::DBus
)

target_link_libraries(qmlcutiefeedbackplugin PUBLIC
    Qt::Core
    Qt::Quick
    cutiefeedback
)

configure_file(src/cutiefeedback.pc.in cutiefeedback.pc @ONLY)

install(TARGETS cutiefeedback
    RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    BUNDLE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(FILES ${CMAKE_BINARY_DIR}/cutiefeedback.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install(TARGETS qmlcutiefeedbackplugin
    RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt6/qml/Cutie/Feedback"
    BUNDLE DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt6/qml/Cutie/Feedback"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt6/qml/Cutie/Feedback"
)

install(DIRECTORY src/qml/Cutie/Feedback DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt6/qml/Cutie")
