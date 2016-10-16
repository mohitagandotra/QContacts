//******************************************************************************
/*! \file
 *
 *  \author Mohita Gandotra
 *
 *  \copyright Copyright (C) 2016 Mohita Gandotra.
 * Contact: mohitagandotra@gmail.com
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
#include "contactsenumerator.h"
#include "types.h"
#include "contactsmodel.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroidExtras>
#endif

#ifdef Q_OS_IOS
#include "ios/ioscontacthandler.h"
#endif

namespace QSIP {

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Mohita Gandotra.
 *
 *  \param[in] model : Contacts model instance.
 *  \param[in] parent : Parent object instance.
 *
 *  \see \ref QSIP::ContactsModel
 ******************************************************************************/
ContactsEnumerator::ContactsEnumerator(ContactsModel* model, QObject *parent) :
    QObject(parent),
    m_model(model)
{
    Q_ASSERT(m_model);
    connect(model, &QObject::destroyed, [this]() { m_model = nullptr;});
}

#ifdef Q_OS_ANDROID
//******************************************************************************
/*! \brief Fetches contacts from the underlying OS and adds it to  the Contacts model,
 *
 *  \details The method blocks untill all contacts are fetched and populated
 *
 *  \author Mohita Gandotra.
 *
 *  \see \ref QSIP::ContactsModel
 ******************************************************************************/
void ContactsEnumerator::fetchContacts()
{
    if(!m_model) {
        return;
    }
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
//******************************************************************************
/*! \brief Fetches contacts from the underlying OS and adds it to  the Contacts model,
 *
 *  \details The method blocks untill all contacts are fetched and populated
 *
 *  \author Mohita Gandotra.
 *
 *  \see \ref QSIP::ContactsModel
 ******************************************************************************/
void ContactsEnumerator::fetchContacts()
{
    if(!m_model) {
        return;
    }
    m_model->clear();
    IosContactHandler handler;
    connect(&handler, &IosContactHandler::newContact,[this](QString id, QString name, QSIP::PhoneNumbers phNos) {
        m_model->addContact(id, name, phNos);
    });
    handler.fetchContacts();
}
#else
//******************************************************************************
/*! \brief Fetches contacts from the underlying OS and adds it to  the Contacts model,
 *
 *  \details The method blocks untill all contacts are fetched and populated
 *
 *  \author Mohita Gandotra.
 *
 *  \see \ref QSIP::ContactsModel
 ******************************************************************************/
void ContactsEnumerator::fetchContacts()
{
    if(!m_model) {
        return;
    }
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

