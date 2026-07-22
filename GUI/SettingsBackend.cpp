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





void SettingsBackend::setHtmlPath(
    const QString& path
)
{
    if(htmlPath_==path)
        return;


    htmlPath_=path;

    emit htmlPathChanged();
}





void SettingsBackend::setSdkPath(
    const QString& path
)
{
    if(sdkPath_==path)
        return;


    sdkPath_=path;

    emit sdkPathChanged();
}




void SettingsBackend::setEnabled(
    bool value
)
{
    if(enabled_==value)
        return;


    enabled_=value;

    emit enabledChanged();
}







void SettingsBackend::setStatusMessage(
    const QString& msg
)
{
    statusMessage_=msg;

    emit statusMessageChanged();
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


    for(auto& i:
        config_.getBlacklist())
    {
        blacklist_
            << QString::fromStdString(i);
    }



    currentTheme_ =
        QString::fromStdString(
            config_.readKeyValue(
                "theme"
            )
        );



    loadThemes();



    emit htmlPathChanged();

    emit sdkPathChanged();

    emit blacklistChanged();

    emit currentThemeChanged();


    setStatusMessage(
        "Reload"
    );
}









void SettingsBackend::save()
{

    config_.setKeyValue(
        "html",
        htmlPath_.toStdString()
    );


    config_.setKeyValue(
        "sdk",
        sdkPath_.toStdString()
    );


    config_.setKeyValue(
        "theme",
        currentTheme_.toStdString()
    );



    if(config_.save())

        setStatusMessage(
            "Saved"
        );

    else

        setStatusMessage(
            "Save failed"
        );
}









void SettingsBackend::addBlacklist(
    const QString& app
)
{

    config_.appendBlacklist(
        app.toStdString()
    );


    reload();

}







void SettingsBackend::removeBlacklist(
    const QString& app
)
{

    config_.removeBlacklist(
        app.toStdString()
    );


    reload();

}









void SettingsBackend::loadThemes()
{

    themeList_.clear();



    std::filesystem::path path =
        g_sdkInitialPath /
        "resources";



    if(!std::filesystem::exists(path))
        return;



    for(auto& item:
        std::filesystem::directory_iterator(path))
    {

        if(item.is_directory())
        {

            themeList_
                <<
                QString::fromStdString(
                    item.path()
                    .filename()
                    .string()
                );

        }

    }


    emit themeListChanged();

}









bool SettingsBackend::uploadTheme(
    const QString& folder
)
{

    QFileInfo info(folder);


    if(!info.exists())
    {
        setStatusMessage(
            "Folder not found"
        );

        return false;
    }



    QString name =
        info.fileName();



    QDir dest(
        QString::fromStdString(
            (
                g_sdkInitialPath /
                "resources"
            ).string()
        )
    );



    if(dest.exists(name))
    {

        setStatusMessage(
            "Theme already exists"
        );

        return false;
    }



    QDir().mkpath(
        dest.absolutePath()
    );



    dest.mkdir(name);



    QDir source(folder);


    for(auto file:
        source.entryList(
            QDir::Files
        ))
    {

        QFile::copy(
            source.filePath(file),
            dest.filePath(
                name+"/"+file
            )
        );

    }



    loadThemes();


    setStatusMessage(
        "Theme uploaded"
    );


    return true;

}









void SettingsBackend::useTheme(
    const QString& name
)
{

    currentTheme_=name;


    emit currentThemeChanged();


    save();


}









void SettingsBackend::removeTheme(
    const QString& name
)
{

    std::filesystem::remove_all(
        g_sdkInitialPath /
        "resources" /
        name.toStdString()
    );


    loadThemes();

}








void SettingsBackend::openThemeFolder(
    const QString& name
)
{

    auto path =
        QString::fromStdString(
            (
                g_sdkInitialPath /
                "resources" /
                name.toStdString()
            ).string()
        );


    QDesktopServices::openUrl(
        QUrl::fromLocalFile(path)
    );

}









bool SettingsBackend::pathExists(
    const QString& path
) const
{
    return QFileInfo::exists(path);
}








void SettingsBackend::enable()
{

    QDBusInterface kwin(
        "org.kde.KWin",
        "/Effects",
        "org.kde.kwin.Effects",
        QDBusConnection::sessionBus()
    );


    kwin.call(
        "loadEffect",
        "ultralightcursor"
    );


}







void SettingsBackend::disable()
{

    QDBusInterface kwin(
        "org.kde.KWin",
        "/Effects",
        "org.kde.kwin.Effects",
        QDBusConnection::sessionBus()
    );


    kwin.call(
        "unloadEffect",
        "ultralightcursor"
    );

}







void SettingsBackend::reloadHtml()
{
    save();
    reconfigureKWin();
}







void SettingsBackend::reconfigureKWin()
{

    QDBusInterface kwin(
        "org.kde.KWin",
        "/KWin",
        "org.kde.KWin"
    );


    kwin.call(
        "reconfigure"
    );

}