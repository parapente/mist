set(QT_USE_QTCORE TRUE)
set(QT_USE_QTGUI TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTWEBKIT TRUE)

set(CMAKE_AUTOMOC ON)

include(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} O2/src/)

set(SRC_LIST mistwebdialog.cpp mistremotefsitem.cpp
main.cpp
mainwindow.cpp
mainwindow.h
mistremotefsmodel.cpp
mistremotefsmodel.h
mainwindow.ui)

QT4_WRAP_UI(mainwin_UI_SRCS mainwindow.ui)

add_subdirectory(O2)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${mainwin_UI_SRCS})
target_link_libraries(${PROJECT_NAME} ${QT_QT_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTWEBKIT_LIBRARY} o2)
