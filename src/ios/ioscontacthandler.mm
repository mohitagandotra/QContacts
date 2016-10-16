#include "ioscontacthandler.h"
#include "ios/ioscontacts.h"

namespace QSIP {
IosContactHandler::IosContactHandler()
{

}

IosContactHandler::~IosContactHandler()
{

}

void IosContactHandler::fetchContacts()
{
    ContactsScan *scanner = [[ContactsScan alloc] init:this];
    [scanner contactScan];
    [scanner release];
}

void IosContactHandler::addNewContact(QString id, QString name, QSIP::PhoneNumbers phNos)
{
    // Emit contact data to recieve it on the Qt thread.
    emit newContact(id, name, phNos);
}

} // namespace QSIP
