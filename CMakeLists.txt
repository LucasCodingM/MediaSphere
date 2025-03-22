cmake_minimum_required(VERSION 3.19)

project(MediaSphere VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick Multimedia LinguistTools QuickControls2)
qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES fr)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appMediaSphere
    src/main.cpp
)

set(TRANSLATION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")
qt6_add_translations(appMediaSphere
    QM_FILES_OUTPUT_VARIABLE qm_files
    TS_FILE_DIR "translations")
install(FILES ${qm_files} DESTINATION ${TRANSLATION_DIR})

# Set the Qt6 policy for QML modules (this suppresses the warning)
qt6_policy(SET QTP0004 NEW)

set(QML_FILES
    src/qml/shared/Main.qml
    src/qml/shared/Header.qml
    src/ResourcesComponents.qml
    src/qml/shared/Enum.qml
    src/qml/shared/menu/MainMenu.qml
    src/qml/shared/menu/MenuPage1.qml
    src/qml/shared/menu/MenuPage2.qml
    src/qml/shared/widgets/Background.qml
    src/qml/shared/widgets/ButtonBack.qml
    src/qml/shared/widgets/ButtonBlueGradient.qml
    src/qml/shared/widgets/ButtonRoundBlueGradient.qml
    src/qml/videoPlayer/VideoPlayer.qml
    src/qml/weather/Weather.qml
    src/qml/weather/WeatherContainer.qml
    src/qml/shared/widgets/ButtonReplay.qml
    src/qml/shared/widgets/ButtonPausePlay.qml
    src/qml/shared/widgets/ButtonAccelerate.qml
    src/qml/shared/widgets/ButtonAudio.qml
    src/qml/shared/widgets/ButtonTransparent.qml
    src/qml/shared/widgets/ControlMedia.qml
    src/qml/shared/widgets/ButtonStop.qml
)

set(RESOURCES
   src/assets/audio.png
   src/assets/back.png
   src/assets/bluetooth.png
   src/assets/buttoncomboBox.png
   src/assets/casque.png
   src/assets/degrees.png
   src/assets/folder.png
   src/assets/gameFlappyBird.png
   src/assets/gameMario.png
   src/assets/gamePacman,.png
   src/assets/gameSnake.png
   src/assets/games.png
   src/assets/iconMediaShere.png
   src/assets/loop.png
   src/assets/mainMenu.png
   src/assets/movie.png
   src/assets/music2.png
   src/assets/music.png
   src/assets/next.png
   src/assets/parameter2.png
   src/assets/parameter.png
   src/assets/pause.png
   src/assets/play.png
   src/assets/plus.png
   src/assets/power.png
   src/assets/previous.png
   src/assets/refresh.png
   src/assets/speaker.png
   src/assets/star.png
   src/assets/trashbin.png
   src/assets/weatherCloudy.png
   src/assets/weatherOvercast.png
   src/assets/weather.png
   src/assets/weatherRain.png
   src/assets/weatherSnow.png
   src/assets/weatherSun.png
   src/assets/weatherMoon.png
   src/assets/weatherOvercastNight.png
   src/assets/weatherWind.png
   src/assets/weatherWindSun.png
   src/assets/mute.png
   src/assets/stop.png
)

set(SOURCES_WEATHER
    src/weather/openmeteoapi.h
    src/weather/openmeteoapi.cpp
)

set(SOURCES_VIDEO_PLAYER
    src/videoPlayer/videoplayer.h
    src/videoPlayer/videoplayer.cpp
    src/videoPlayer/videoselectionmodel.h
    src/videoPlayer/videoselectionmodel.cpp
    src/videoPlayer/videothumbnailextractor.h
    src/videoPlayer/videothumbnailextractor.cpp
    src/videoPlayer/videoworker.h
    src/videoPlayer/videoworker.cpp
)

set(SOURCES_SHARED
    src/shared/logger/logger.h
    src/shared/logger/logger.cpp
    src/shared/customexception.h
    src/shared/global.h
    src/shared/global.cpp
)

set_source_files_properties(src/ResourcesComponents.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appMediaSphere
    URI MediaSphere
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
set_target_properties(appMediaSphere PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMediaSphere
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMediaSphere
    PRIVATE Qt6::Quick
    Qt6::Multimedia
    Qt6::Core
    Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appMediaSphere
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
