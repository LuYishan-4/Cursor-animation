#pragma once

#include <QObject>
#include <QString>

#include "../src/lib/header/UserConfig.hpp"



class SettingsBackend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString htmlPath READ htmlPath WRITE setHtmlPath NOTIFY htmlPathChanged)
    Q_PROPERTY(QString sdkPath READ sdkPath WRITE setSdkPath NOTIFY sdkPathChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)

public:

    explicit SettingsBackend(QObject* parent = nullptr);


    QString htmlPath() const;
    void setHtmlPath(const QString& path);

    QString sdkPath() const;
    void setSdkPath(const QString& path);

    bool enabled() const;
    void setEnabled(bool value);

    QString statusMessage() const;


    Q_INVOKABLE void save();

    Q_INVOKABLE void reload();

    Q_INVOKABLE void reconfigureKWin();

    Q_INVOKABLE bool pathExists(const QString& path) const;


public Q_SLOTS:


    void enable();

    void disable();

    void reloadHtml();


Q_SIGNALS:

    void htmlPathChanged();
    void sdkPathChanged();
    void enabledChanged();
    void statusMessageChanged();


private:

    void setStatusMessage(const QString& message);

    UltralightWebCursorM::UserConfig config_;

    QString htmlPath_;
    QString sdkPath_;
    bool enabled_ = true;

    QString statusMessage_;

};