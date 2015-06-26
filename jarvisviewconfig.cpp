#include "jarvisviewconfig.h"

#include <QStandardPaths>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


JarvisConfig::JarvisConfig(const QString &viewName):
    m_bValid(false),
    m_sName(viewName)
{
    QString viewConfigFile = QStandardPaths::standardLocations(QStandardPaths::GenericConfigLocation).first();
    viewConfigFile.append("/jarvis/views/");
    viewConfigFile.append(viewName);
    viewConfigFile.append(".json");

    QFile conf(viewConfigFile);

    if ( !conf.exists() )
    {
        qDebug() << "Config file not found" << viewConfigFile;
        return;
    }

    if (!conf.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open config file" << viewConfigFile;
        return;
    }

    QByteArray fjson = conf.readAll();

    QJsonParseError err;
    m_sJsonDoc = QJsonDocument::fromJson( fjson, &err);
    if (err.error != QJsonParseError::NoError)
    {
        qDebug() << "Json load failed: " <<  err.errorString();
        return ;
    }


     QMap<QString, QVariant> map = m_sJsonDoc.object().toVariantMap();

    QMap<QString, ConfigurationProperty> bridgeMap;

#define POPULATEMAP(t) bridgeMap[ QString(#t).replace("Prop", "").toLower() ] = t;

    POPULATEMAP(PropHeight);
    POPULATEMAP(PropWidth);
    POPULATEMAP(PropX);
    POPULATEMAP(PropY);
    POPULATEMAP(PropThemeFile);
    POPULATEMAP(PropForceDesktop);

    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        m_mProperties[ bridgeMap[i.key()] ] = i.value();
    }

    m_bValid = true;
}

QVariant JarvisConfig::confProp(JarvisConfig::ConfigurationProperty p) const
{
    return m_mProperties[p];
}

const QString &JarvisConfig::name() const
{
    return m_sName;
}

bool JarvisConfig::isValid() const
{
    return m_bValid;
}


