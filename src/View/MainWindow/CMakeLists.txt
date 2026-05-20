find_package(Qt6 6.2 COMPONENTS  Core Quick Sql REQUIRED)

set(MainWindow_SOURCES
    mainwindow.cpp
    mainwindow.h
)

qt6_wrap_cpp(MainWindow_MOC_SOURCES mainwindow.h)

add_library(MainWindow STATIC
    ${MainWindow_SOURCES}
    ${MainWindow_MOC_SOURCES}
)

target_link_libraries(MainWindow PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Sql
    DataBaseModel
)

target_include_directories(MainWindow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(MainWindow INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Model/DataBaseModel
)
