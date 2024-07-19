cmake_minimum_required(VERSION 3.5)

project(untitled VERSION 0.1 LANGUAGES CXX)

string( TOLOWER ${PROJECT_NAME} TARGET_NAME )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/identifier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/supplySystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/product.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/warehouse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/sparePart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/supplyPartGroup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/addgroupdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/deletegroupgialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/addpartdialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/addpartstodialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/mainwindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sparePart.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sparePartGroup.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/product.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/supplySystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/identifier.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/warehouse.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sparePartRecord.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/addgroupdialog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/deletegroupgialog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/addpartdialog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/addpartstodialog.h
)
qt5_wrap_ui( UIS_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/uis/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/uis/addgroupdialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/uis/deletegroupgialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/uis/addpartdialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/uis/addpartstodialog.ui
)

set( TARGET_SOURCE_DIRS
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/uis
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/source
)

add_executable(${TARGET_NAME} ${PROJECT_SOURCES} ${TARGET_SOURCE_DIRS} ${UIS_HDRS})
target_include_directories( ${TARGET_NAME} PRIVATE ${TARGET_SOURCE_DIRS} )
target_compile_definitions( ${TARGET_NAME} PRIVATE -DDISABLE_STATIC_HASH )

target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(untitled PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

