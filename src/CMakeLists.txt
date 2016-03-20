set(CMAKE_AUTOMOC ON)

#include(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} O2/src/)

set(SRC_LIST mistwebdialog.cpp mistremotefsitem.cpp
main.cpp
mainwindow.cpp
mainwindow.h
mistremotefsmodel.cpp
mainwindow.ui
hubicconnection.cpp
reqqueue.cpp
reqqueueitem.cpp)

QT5_WRAP_UI(mainwin_UI_SRCS mainwindow.ui)

set(WITH_HUBIC TRUE)
set(WITH_QT5 TRUE)

add_subdirectory(O2)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${mainwin_UI_SRCS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets Qt5::WebKitWidgets o2)
