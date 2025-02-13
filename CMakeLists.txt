cmake_minimum_required(VERSION 3.16)

project(RaspGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick Multimedia)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appRaspGui
    main.cpp
)
# Set the Qt6 policy for QML modules (this suppresses the warning)
#qt6_policy(SET QTP0004 NEW)

set(QML_FILES
    qml/shared/Main.qml
    qml/shared/Header.qml
    ResourcesComponents.qml
    qml/shared/Enum.qml
    qml/shared/menu/Menu.qml
    qml/shared/menu/MenuPage1.qml
    qml/shared/menu/MenuPage2.qml
    qml/shared/widgets/Background.qml
    qml/shared/widgets/ButtonBack.qml
    qml/shared/widgets/ButtonBlueGradient.qml
    qml/shared/widgets/ButtonRoundBlueGradient.qml
    qml/videoPlayer/VideoPlayer.qml
    qml/weather/Weather.qml
    qml/weather/WeatherContainer.qml
)

set(RESOURCES
   assets/audio.png
   assets/back.png
   assets/bluetooth.png
   assets/buttoncomboBox.png
   assets/casque.png
   assets/degrees.png
   assets/folder.png
   assets/gameFlappyBird.png
   assets/gameMario.png
   assets/gamePacman,.png
   assets/gameSnake.png
   assets/games.png
   assets/loop.png
   assets/mainMenu.png
   assets/movie.png
   assets/music2.png
   assets/music.png
   assets/next.png
   assets/parameter2.png
   assets/parameter.png
   assets/pause.png
   assets/play.png
   assets/plus.png
   assets/power.png
   assets/previous.png
   assets/refresh.png
   assets/speaker.png
   assets/star.png
   assets/trashbin.png
   assets/weatherCloudy.png
   assets/weatherOvercast.png
   assets/weather.png
   assets/weatherRain.png
   assets/weatherSnow.png
   assets/weatherSun.png
)

set(SOURCES_WEATHER
    weather/openmeteoapi.h
    weather/openmeteoapi.cpp
)

set(SOURCES_VIDEO_PLAYER
    videoPlayer/videoplayer.h
    videoPlayer/videoplayer.cpp
)

set(SOURCES_SHARED
    shared/logger/logger.h
    shared/logger/logger.cpp
    shared/customexception.h
)

set_source_files_properties(ResourcesComponents.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

# # Set the path to the QML files
# # Copy QML files to the build output directory
# file(COPY ${QML_FILES} DESTINATION ${CMAKE_BINARY_DIR}/qml)

# # Install QML files to the final package location
# install(DIRECTORY qml/ DESTINATION ${CMAKE_INSTALL_PREFIX}/qml)

# # Set QML import path
# set_target_properties(appRaspGui PROPERTIES
#     QML_IMPORT_PATH ${CMAKE_BINARY_DIR}/qml
# )

qt_add_qml_module(appRaspGui
    URI RaspGui
    VERSION 1.0
    QML_FILES
        ${QML_FILES}
    RESOURCES
        ${RESOURCES}
    SOURCES
        ${SOURCES_WEATHER}
        ${SOURCES_VIDEO_PLAYER}
        ${SOURCES_SHARED}

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
    Qt6::Multimedia
    Qt6::Core
)

include(GNUInstallDirs)
install(TARGETS appRaspGui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
