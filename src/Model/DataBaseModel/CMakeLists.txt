find_package(Qt6 6.2 REQUIRED COMPONENTS Core Quick PrintSupport Sql)


add_library(DataBaseModel STATIC
  databasemodel.cpp
  databasemodel.h
)

target_link_libraries(DataBaseModel PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::PrintSupport
  Qt6::Sql
)
