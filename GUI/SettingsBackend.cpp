#include "SettingsBackend.hpp"

#include <QDBusInterface>
#include <QDBusReply>
#include <QFileInfo>


SettingsBackend::SettingsBackend(QObject* parent)
    : QObject(parent)
{
    reload();
}


QString SettingsBackend::htmlPath() const
{
    return htmlPath_;
}


void SettingsBackend::setHtmlPath(const QString& path)
{
    if(htmlPath_ == path)
        return;

    htmlPath_ = path;
    Q_EMIT htmlPathChanged();
}


QString SettingsBackend::sdkPath() const
{
    return sdkPath_;
}


void SettingsBackend::setSdkPath(const QString& path)
{
    if(sdkPath_ == path)
        return;

    sdkPath_ = path;
    Q_EMIT sdkPathChanged();
}


bool SettingsBackend::enabled() const
{
    return enabled_;
}


void SettingsBackend::setEnabled(bool value)
{
    if(enabled_ == value)
        return;

    enabled_ = value;
    Q_EMIT enabledChanged();
}


QString SettingsBackend::statusMessage() const
{
    return statusMessage_;
}


void SettingsBackend::setStatusMessage(const QString& message)
{
    statusMessage_ = message;
    Q_EMIT statusMessageChanged();
}


void SettingsBackend::save()
{
    config_.setKeyValue("html",htmlPath_.toStdString());
    config_.setKeyValue("sdk",sdkPath_.toStdString());


    if(config_.save())
    {
        setStatusMessage(QStringLiteral("已儲存設定"));
    }
    else
    {
        setStatusMessage(QStringLiteral("儲存失敗，請檢查權限"));
    }
}


void SettingsBackend::reload()
{
    config_.load();

    htmlPath_ = QString::fromStdString(config_.readKeyValue("html"));
    sdkPath_ = QString::fromStdString(config_.readKeyValue("sdk"));
    enabled_ = true;

    Q_EMIT htmlPathChanged();
    Q_EMIT sdkPathChanged();
    Q_EMIT enabledChanged();

    setStatusMessage(QStringLiteral("重新載入"));
}


void SettingsBackend::reconfigureKWin()
{
    QDBusInterface kwin(
        QStringLiteral("org.kde.KWin"),
        QStringLiteral("/KWin"),
        QStringLiteral("org.kde.KWin")
    );

    if(!kwin.isValid())
    {
        return;
    }

    QDBusReply<void> reply = kwin.call(QStringLiteral("reconfigure"));

    if(reply.isValid())
    {
        setStatusMessage(QStringLiteral("reload"));
    }
    else
    {
        setStatusMessage(QStringLiteral("failed: ") + reply.error().message());
    }
}


bool SettingsBackend::pathExists(const QString& path) const
{
    return QFileInfo::exists(path);
}


void SettingsBackend::enable()
{
    QDBusInterface kwin(
        QStringLiteral("org.kde.KWin"),
        QStringLiteral("/Effects"),
        QStringLiteral("org.kde.kwin.Effects"),
        QDBusConnection::sessionBus()
    );

    kwin.call(
        QStringLiteral("loadEffect"),
        QStringLiteral("ultralightcursor")
    );

    setStatusMessage(QStringLiteral("已啟用特效"));
}


void SettingsBackend::disable()
{
    QDBusInterface kwin(
        QStringLiteral("org.kde.KWin"),
        QStringLiteral("/Effects"),
        QStringLiteral("org.kde.kwin.Effects"),
        QDBusConnection::sessionBus()
    );

    kwin.call(
        QStringLiteral("unloadEffect"),
        QStringLiteral("ultralightcursor")
    );

    setStatusMessage(QStringLiteral("已關閉特效"));
}


void SettingsBackend::reloadHtml()
{
    save();
    reconfigureKWin();
}