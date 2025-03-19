cmake_minimum_required(VERSION 3.19)

project(MediaSphere VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick Multimedia LinguistTools QuickControls2)
qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES fr)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appMediaSphere
    main.cpp
)

set(TRANSLATION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")
qt6_add_translations(appMediaSphere
    QM_FILES_OUTPUT_VARIABLE qm_files
    TS_FILE_DIR "translations")
install(FILES ${qm_files} DESTINATION ${TRANSLATION_DIR})

# Set the Qt6 policy for QML modules (this suppresses the warning)
qt6_policy(SET QTP0004 NEW)

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
    qml/shared/widgets/ButtonReplay.qml
    qml/shared/widgets/ButtonPausePlay.qml
    qml/shared/widgets/ButtonAccelerate.qml
    qml/shared/widgets/ButtonAudio.qml
    qml/shared/widgets/ButtonTransparent.qml
    qml/shared/widgets/ControlMedia.qml
    qml/shared/widgets/ButtonStop.qml
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
   assets/iconMediaShere.png
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
   assets/weatherMoon.png
   assets/weatherOvercastNight.png
   assets/weatherWind.png
   assets/weatherWindSun.png
   assets/mute.png
   assets/stop.png
)

set(SOURCES_WEATHER
    weather/openmeteoapi.h
    weather/openmeteoapi.cpp
)

set(SOURCES_VIDEO_PLAYER
    videoPlayer/videoplayer.h
    videoPlayer/videoplayer.cpp
    videoPlayer/videoselectionmodel.h
    videoPlayer/videoselectionmodel.cpp
    videoPlayer/videothumbnailextractor.h
    videoPlayer/videothumbnailextractor.cpp
    videoPlayer/videoworker.h
    videoPlayer/videoworker.cpp
)

set(SOURCES_SHARED
    shared/logger/logger.h
    shared/logger/logger.cpp
    shared/customexception.h
    shared/global.h
    shared/global.cpp
)

set_source_files_properties(ResourcesComponents.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

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
