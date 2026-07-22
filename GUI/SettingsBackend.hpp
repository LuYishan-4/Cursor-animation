#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

#include "../src/lib/header/UserConfig.hpp"


class SettingsBackend : public QObject
{
    Q_OBJECT


    Q_PROPERTY(
        QString htmlPath
        READ htmlPath
        WRITE setHtmlPath
        NOTIFY htmlPathChanged
    )


    Q_PROPERTY(
        QString sdkPath
        READ sdkPath
        WRITE setSdkPath
        NOTIFY sdkPathChanged
    )


    Q_PROPERTY(
        bool enabled
        READ enabled
        WRITE setEnabled
        NOTIFY enabledChanged
    )


    Q_PROPERTY(
        QString statusMessage
        READ statusMessage
        NOTIFY statusMessageChanged
    )


    Q_PROPERTY(
        QStringList blacklist
        READ blacklist
        NOTIFY blacklistChanged
    )


    Q_PROPERTY(
        QStringList themeList
        READ themeList
        NOTIFY themeListChanged
    )


    Q_PROPERTY(
        QString currentTheme
        READ currentTheme
        NOTIFY currentThemeChanged
    )



public:


    explicit SettingsBackend(
        QObject* parent=nullptr
    );



    QString htmlPath() const;

    QString sdkPath() const;

    bool enabled() const;

    QString statusMessage() const;


    QStringList blacklist() const;

    QStringList themeList() const;


    QString currentTheme() const;




    void setHtmlPath(
        const QString&
    );


    void setSdkPath(
        const QString&
    );


    void setEnabled(
        bool
    );



    Q_INVOKABLE void save();

    Q_INVOKABLE void reload();


    Q_INVOKABLE void enable();

    Q_INVOKABLE void disable();


    Q_INVOKABLE void reloadHtml();


    Q_INVOKABLE void reconfigureKWin();



    Q_INVOKABLE bool pathExists(
        const QString&
    ) const;




    // blacklist

    Q_INVOKABLE void addBlacklist(
        const QString&
    );


    Q_INVOKABLE void removeBlacklist(
        const QString&
    );




    // theme

    Q_INVOKABLE bool uploadTheme(
        const QString& path
    );


    Q_INVOKABLE void useTheme(
        const QString& name
    );


    Q_INVOKABLE void removeTheme(
        const QString& name
    );


    Q_INVOKABLE void openThemeFolder(
        const QString& name
    );



signals:


    void htmlPathChanged();

    void sdkPathChanged();

    void enabledChanged();

    void statusMessageChanged();



    void blacklistChanged();


    void themeListChanged();


    void currentThemeChanged();



private:


    void setStatusMessage(
        const QString&
    );


    void loadThemes();



private:


    QString htmlPath_;

    QString sdkPath_;


    bool enabled_=true;


    QString statusMessage_;



    QStringList blacklist_;


    QStringList themeList_;


    QString currentTheme_;



    UltralightWebCursorM::UserConfig config_;

};