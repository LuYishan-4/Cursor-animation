set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


include(KDEInstallDirs)
include(KDECMakeSettings)
kcmutils_add_qml_kcm(

    kcm_ultralightwebcursor


    SOURCES

       main_settings.cpp
       main_settings.hpp

        SettingsBackend.cpp
        SettingsBackend.hpp
        ${CMAKE_SOURCE_DIR}/src/lib/UserConfig.cpp
        ${CMAKE_SOURCE_DIR}/src/lib/header/UserConfig.hpp
        ${CMAKE_SOURCE_DIR}/src/lib/Quick/PluginPath/PluginPath.cpp
        ${CMAKE_SOURCE_DIR}/src/lib/Quick/PluginPath/PluginPath.hpp


)



target_include_directories(
    kcm_ultralightwebcursor
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)



target_link_libraries(

    kcm_ultralightwebcursor

    PRIVATE


    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::DBus


    KF6::CoreAddons
    KF6::ConfigCore
    KF6::ConfigWidgets
    KF6::KCMUtils
    KF6::I18n

)
install(
    FILES kcm_ultralightwebcursor.json
    DESTINATION ${CMAKE_INSTALL_DATADIR}/kservices6
)