find_package(Qt6 6.2 REQUIRED COMPONENTS Core Quick PrintSupport Sql)


set(DataBaseModel_SOURCES
  databasemodel.cpp
  databasemodel.h
)
qt6_wrap_cpp(DataBaseModel_MOC_SOURCES databasemodel.h)
add_library(DataBaseModel STATIC ${DataBaseModel_SOURCES} ${DataBaseModel_MOC_SOURCES})

target_link_libraries(DataBaseModel PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::PrintSupport
    Qt6::Sql
)

target_include_directories(DataBaseModel
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
