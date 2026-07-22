#include "SettingsBackend.hpp"

#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QDBusInterface>
#include <QDBusConnection>

#include <filesystem>


using namespace UltralightWebCursorM;



SettingsBackend::SettingsBackend(
    QObject* parent
)
    : QObject(parent)
{
    reload();
}



QString SettingsBackend::htmlPath() const
{
    return htmlPath_;
}



QString SettingsBackend::sdkPath() const
{
    return sdkPath_;
}



bool SettingsBackend::enabled() const
{
    return enabled_;
}



QString SettingsBackend::statusMessage() const
{
    return statusMessage_;
}



QStringList SettingsBackend::blacklist() const
{
    return blacklist_;
}



QStringList SettingsBackend::themeList() const
{
    return themeList_;
}



QString SettingsBackend::currentTheme() const
{
    return currentTheme_;
}





void SettingsBackend::setHtmlPath(const QString& path)
{
    if(htmlPath_ == path)
        return;


    htmlPath_ = path;


    Q_EMIT htmlPathChanged();
}





void SettingsBackend::setSdkPath(
    const QString& path
)
{
    if(sdkPath_ == path)
        return;


    sdkPath_ = path;


    Q_EMIT sdkPathChanged();
}





void SettingsBackend::setEnabled(
    bool value
)
{
    if(enabled_ == value)
        return;


    enabled_ = value;


    Q_EMIT enabledChanged();
}





void SettingsBackend::setStatusMessage(
    const QString& msg
)
{
    statusMessage_ = msg;


    Q_EMIT statusMessageChanged();
}






void SettingsBackend::reload()
{

    config_.load();



    htmlPath_ =
        QString::fromStdString(
            config_.readKeyValue("html")
        );



    sdkPath_ =
        QString::fromStdString(
            config_.readKeyValue("sdk")
        );



    blacklist_.clear();



    for(auto& item :
        config_.getBlacklist())
    {

        blacklist_
            <<
            QString::fromStdString(item);

    }


  currentTheme_ =
        QString::fromStdString(
            config_.currentTheme();
        );



    loadThemes();
    Q_EMIT htmlPathChanged();
    Q_EMIT sdkPathChanged();
    Q_EMIT blacklistChanged();
    Q_EMIT themeListChanged();
    setStatusMessage(
        QStringLiteral("Reload")
    );

}
void SettingsBackend::save(){

    config_.setKeyValue(
        "html",
        htmlPath_.toStdString()
    );
    config_.setKeyValue(
        "sdk",
        sdkPath_.toStdString()
    );


    if(config_.save()){
        setStatusMessage(
            QStringLiteral("Saved")
        );
    }else{
        setStatusMessage(
            QStringLiteral("Save failed")
        );
    }
}

void SettingsBackend::addBlacklist(const QString& app){

    config_.appendBlacklist(
        app.toStdString()
    );

    reload();
}


void SettingsBackend::removeBlacklist(const QString& app){
    config_.removeBlacklist(
        app.toStdString()
    );
    reload();
}
void SettingsBackend::loadThemes(){
    themeList_.clear();

    std::filesystem::path path =
        g_sdkInitialPath /
        "resources";

    if(!std::filesystem::exists(path))
        return;

    for(auto& item :std::filesystem::directory_iterator(path)){
        if(item.is_directory()){
            themeList_
                <<
                QString::fromStdString(
                    item.path()
                    .filename()
                    .string()
                );

        }

    }
    Q_EMIT themeListChanged();
}