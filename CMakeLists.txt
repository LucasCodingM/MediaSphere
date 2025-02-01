cmake_minimum_required(VERSION 3.16)

project(RaspGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appRaspGui
    main.cpp
)

set_source_files_properties(ResourcesComponents.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appRaspGui
    URI RaspGui
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES Header.qml
        QML_FILES Background.qml
        QML_FILES ButtonBlueGradient.qml
        QML_FILES Menu.qml
        QML_FILES MenuPage1.qml
        QML_FILES MenuPage2.qml
        RESOURCES assets/audio.png assets/back.png assets/bluetooth.png assets/buttoncomboBox.png assets/casque.png assets/folder.png assets/gameFlappyBird.png assets/gameMario.png assets/gamePacman,.png assets/games.png assets/gameSnake.png assets/loop.png assets/mainMenu.png assets/movie.png assets/music.png assets/music2.png assets/next.png assets/parameter.png assets/parameter2.png assets/pause.png assets/play.png assets/plus.png assets/power.png assets/previous.png assets/speaker.png assets/star.png assets/trashbin.png assets/weather.png assets/weatherCloudy.png assets/weatherRain.png assets/weatherSun.png
        QML_FILES Weather.qml
        QML_FILES ResourcesComponents.qml
        QML_FILES ButtonBack.qml
        SOURCES openmeteoapi.h openmeteoapi.cpp
        QML_FILES Enum.qml
        SOURCES logger.h logger.cpp
        SOURCES customexception.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appRaspGui PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appRaspGui
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appRaspGui
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appRaspGui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
