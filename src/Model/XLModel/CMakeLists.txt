find_package(Qt6 6.2 REQUIRED COMPONENTS Core Quick PrintSupport Sql)


add_library(XLModel STATIC
  xlmodel.cpp
  xlmodel.h
)
target_include_directories(XLModel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QXlsx-master/QXlsx/header)

target_link_libraries(XLModel PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::PrintSupport
  Qt6::Sql
  QXlsx::QXlsx       # подключаем QXlsx через target
)
