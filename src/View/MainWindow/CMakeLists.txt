find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)

add_library(MainWindow
    STATIC
    MainWindow.cpp
)


target_link_libraries(MainWindow PRIVATE Qt6::Quick)
target_link_libraries(MainWindow PRIVATE Qt6::PrintSupport)
target_include_directories(MainWindow INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


#target_link_directories(MainView PUBLIC ../../Controller)
#target_link_libraries(MainView PUBLIC MainManager)
