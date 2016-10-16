#ifndef CONTACT_H
#define CONTACT_H

#include "types.h"
#include <QObject>
#include <QHash>
#include <QPair>
namespace QSIP {

class Contact : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString contactID READ contactID)
    Q_PROPERTY(QString contactName READ contactName WRITE setContactName NOTIFY contactNameChanged)

public:
    explicit Contact(QString id, QString name, PhoneNumbers numbers, QObject *parent = 0);

public:
    QString contactID() const { return m_id; }

    QString contactName() const { return m_name; }
    void setContactName(const QString &newName);
    PhoneNumbers contactNumbers() const;

signals:
    void contactNameChanged();

public slots:

private:
    QString m_id;
    QString m_name;
    PhoneNumbers m_phoneNumbers;
};

} // namespace QSIP
#endif // CONTACT_H
