#pragma once

#include <KQuickConfigModule>
#include <KPluginFactory>


class SettingsBackend;


class UIKCM : public KQuickConfigModule
{
    Q_OBJECT

public:

    UIKCM(
        QObject* parent,
        const KPluginMetaData& metaData
    );

    ~UIKCM() override;


    void load() override;

    void save() override;

    void defaults() override;


private:

    SettingsBackend* m_backend = nullptr;

};