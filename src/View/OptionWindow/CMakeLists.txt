find_package(Qt6 REQUIRED COMPONENTS Core Quick Sql)

set(OptionWindow_V_SOURCES
    optionwindow_v.cpp
    optionwindow_v.h
)

qt6_wrap_cpp(OptionWindow_V_MOC_SOURCES optionwindow_v.h)

add_library(OptionWindow_V STATIC
    ${OptionWindow_V_SOURCES}
    ${OptionWindow_V_MOC_SOURCES}
)

target_link_libraries(OptionWindow_V PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Sql
    XLModel
    DataBaseModel
)

target_include_directories(OptionWindow_V PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(OptionWindow_V INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Model/XLModel
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Model/DataBaseModel
)
