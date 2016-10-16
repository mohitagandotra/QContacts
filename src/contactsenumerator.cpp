#include "contactsenumerator.h"
#include "types.h"
#include "contactsmodel.h"
#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroidExtras>
#endif

#ifdef Q_OS_IOS
#include "ios/ioscontacthandler.h"
#endif

namespace QSIP {

ContactsEnumerator::ContactsEnumerator(ContactsModel* model, QObject *parent) :
    QObject(parent),
    m_model(model)
{
}

#ifdef Q_OS_ANDROID
void ContactsEnumerator::fetchContacts()
{
    m_model->clear();
    QAndroidJniObject contacts = QtAndroid::androidActivity().callObjectMethod("readContacts","()[Ljava/lang/String;");
    QAndroidJniEnvironment env;
    int size = env->GetArrayLength(contacts.object<jarray>());
    for (int i=0; i < size; ++i) {
        QAndroidJniObject arrayElemen = env->GetObjectArrayElement(contacts.object<jobjectArray>(), i);
        QString jsonData = arrayElemen.toString();
        QByteArray rawData = jsonData.toUtf8();
        QJsonParseError p;
        QJsonDocument contacts = QJsonDocument::fromJson(rawData,&p);
        QJsonObject contactInfo = contacts.object();
        QString id;
        QString name;
        PhoneNumbers phoneNumbers;
        foreach (QString key, contactInfo.keys()) {
            QString value = contactInfo.value(key).toString();
            if(key.compare("id") == 0) {
                id = value;
            } else if(key.compare("name") == 0) {
                name = value;
            } else {
                phoneNumbers.append({key,value});
            }
        }
        m_model->addContact(id, name, phoneNumbers);
    }
}
#elif defined Q_OS_IOS
void ContactsEnumerator::fetchContacts()
{
    m_model->clear();
    IosContactHandler handler;
    connect(&handler, &IosContactHandler::newContact,[this](QString id, QString name, QSIP::PhoneNumbers phNos) {
        m_model->addContact(id, name, phNos);
    });
    handler.fetchContacts();
}
#else
void ContactsEnumerator::fetchContacts()
{
    m_model->clear();
    PhoneNumbers testNos;
    testNos.append({"Mobile", "+34 67774888"});
    testNos.append({"Home", "+22 23774888"});
    m_model->addContact("1", "John", testNos);
    m_model->addContact("2", "Peter", testNos);
    m_model->addContact("3", "Hanks", testNos);
}
#endif

} // namespace QSIP

