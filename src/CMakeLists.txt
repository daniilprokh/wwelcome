set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(MAIN_SOURCES
    main.cpp
)

set(HEADERS
    welcome_window.h
    settings_widget.h
)

set(SOURCES
    welcome_window.cpp
    settings_widget.cpp
)

set(Qt5_DIR "D:/Soft/Programming/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Multimedia REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

qt5_wrap_ui(UI_FILES
    welcome_window.ui
    settings_widget.ui
)

qt5_add_resources(QRC_WRAPPERS resource.qrc OPTIONS -no-compress)

add_executable (${PROJECT_NAME}
    ${MAIN_SOURCES} ${SOURCES} ${HEADERS}
    ${UI_FILES} ${QRC_WRAPPERS}
)

target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Widgets Qt5::Multimedia)

install(FILES $<TARGET_FILE:Qt5::Widgets> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES $<TARGET_FILE:Qt5::Gui> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES $<TARGET_FILE:Qt5::Multimedia> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES $<TARGET_FILE:Qt5::Network> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if(WIN32)
    install(DIRECTORY "${Qt5_DIR}/../../../plugins/platforms" DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    install(DIRECTORY "${Qt5_DIR}/../../../plugins/mediaservice" DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
