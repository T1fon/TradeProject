cmake_minimum_required(VERSION 3.16)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 3)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

project(TradeProject VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

add_subdirectory(src)

qt_standard_project_setup()

qt_add_executable(appTradeProject
    src/main.cpp
)

qt_add_qml_module(appTradeProject
    URI TradeProject
    VERSION 1.0
    QML_FILES src/Main.qml
    QML_FILES src/View/OptionWindow/OptionWindow_V.qml
    RESOURCES src/View/OptionWindow/CMakeLists.txt
    RESOURCES src/Model/CMakeLists.txt
    SOURCES src/Model/XLModel/xlmodel.h src/Model/XLModel/xlmodel.cpp
    RESOURCES src/Model/XLModel/CMakeLists.txt
)
target_compile_definitions(appTradeProject PRIVATE PROJECT_VERSION="${PROJECT_VERSION}")

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTradeProject PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTradeProject
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTradeProject
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appTradeProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
