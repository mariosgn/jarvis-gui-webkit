#ifndef JARVISVIEWCONFIG_H
#define JARVISVIEWCONFIG_H

#include <QJsonDocument>
#include <QObject>
#include <QVariant>

class JarvisConfig : public QObject
{
    Q_OBJECT
public:
    enum ConfigurationProperty {
        PropWidth,
        PropHeight,
        PropX,
        PropY,
        PropThemeFile,
        PropForceDesktop,
    } ;

    explicit JarvisConfig( const QString& viewName);

    QVariant confProp( ConfigurationProperty p) const;
    const QString& name() const;

    bool isValid() const;

signals:

public slots:

private:
    QJsonDocument m_sJsonDoc;
    QMap<ConfigurationProperty, QVariant> m_mProperties;
    bool m_bValid;
    QString m_sName;
};

#endif // JARVISVIEWCONFIG_H
