find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)

add_library(XLModel
    STATIC
    xlmodel.cpp
)
add_subdirectory(qxlsx/QXlsx)

target_link_libraries(XLModel PRIVATE Qt6::Core)
target_link_libraries(XLModel PRIVATE QXlsx)
