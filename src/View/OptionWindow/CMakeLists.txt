find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)

add_library(OptionWindow_V
    STATIC
    optionwindow_v.cpp
)


target_link_libraries(OptionWindow_V PRIVATE Qt6::Quick)
target_link_libraries(OptionWindow_V PRIVATE Qt6::SerialPort)

target_include_directories(OptionWindow_V INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


#target_link_directories(EmulatorView PUBLIC ../../Controller)
#target_link_libraries(EmulatorView PUBLIC MainManager)
