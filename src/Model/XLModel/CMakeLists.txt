find_package(Qt6 6.2 REQUIRED COMPONENTS Core Quick PrintSupport Sql)

set(XLModel_SOURCES
    xlmodel.cpp
    xlmodel.h
)

qt6_wrap_cpp(XLModel_MOC_SOURCES xlmodel.h)

add_library(XLModel STATIC ${XLModel_SOURCES} ${XLModel_MOC_SOURCES})

target_link_libraries(XLModel PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::PrintSupport
    Qt6::Sql
    QXlsx::QXlsx
)

target_include_directories(XLModel
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../QXlsx/QXlsx/header
)
