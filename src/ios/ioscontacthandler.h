#ifndef IOSCONTACTHANDLER_H
#define IOSCONTACTHANDLER_H

#include <QObject>
#include "types.h"

namespace QSIP {

class IosContactHandler : public QObject
{
    Q_OBJECT
public:
    IosContactHandler();
    ~IosContactHandler();

    void fetchContacts();
    void addNewContact(QString id, QString name, QSIP::PhoneNumbers phNos);

signals:
    void newContact(QString id, QString name, QSIP::PhoneNumbers);
};

} // namespace QSIP
#endif // IOSCONTACTHANDLER_H
