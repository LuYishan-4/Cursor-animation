set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



kcmutils_add_qml_kcm(

    kcm_ultralightwebcursor


    SOURCES

       main_settings.cpp
       main_settings.hpp

        SettingsBackend.cpp
        SettingsBackend.hpp

)



target_include_directories(

    kcm_ultralightwebcursor

    PRIVATE

    ${CMAKE_CURRENT_SOURCE_DIR}

    ${CMAKE_SOURCE_DIR}/src/lib/header

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