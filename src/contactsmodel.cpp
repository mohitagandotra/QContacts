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
#include "contactsmodel.h"
#include "contact.h"

namespace QSIP {

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Mohita Gandotra.
 *
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
ContactsModel::ContactsModel(QObject *parent) : QAbstractListModel(parent)
{

}

//******************************************************************************
/*! \brief Returns the model's role names.
 *
 *  \author Mohita Gandotra
 *
 *  \return QHash<int, QByteArray> : Hash of role id's and role names.
 ******************************************************************************/
QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CONTACT_ID] = "contact_id";
    roles[CONTACT_NAME] = "contact_name";
    roles[CONTACT_IMAGE] = "contact_image";
    roles[CONTACT_PHONE_NUMBERS] = "contact_phone_numbers";
    return roles;
}

//******************************************************************************
/*! \brief Add a thema instance to the model. Ownership is maintained by the model.
 *
 *  \author Mohita Gandotra
 *
 *  \param[in] contactID : Unique identifier of the contact.
 *  \param[in] name : Name of the contact.
 *  \param[in] phoneNumbers : Phone numbers associated with the contacts.
 ******************************************************************************/
void ContactsModel::addContact(QString contactID, QString name, PhoneNumbers phoneNumbers)
{
    beginInsertRows(QModelIndex(),m_data.count(),m_data.count());
    m_data.append(new Contact(contactID, name, phoneNumbers, this));
    endInsertRows();
}

//******************************************************************************
/*! \brief Clears the contacts data.
 *
 *  \author Mohita Gandotra
 ******************************************************************************/
void ContactsModel::clear()
{
    beginResetModel();
    foreach(Contact* contact, m_data)
        delete contact;
    m_data.clear();
    endResetModel();
}

//******************************************************************************
/*! \brief Returns the data stored under the given role for the item referred
 *  to by the index.
 *
 *  \author Mohita Gandotra
 *
 *  \param[in] index : Index of the item refered.
 *  \param[in] role : Role id to be accessed.
 *
 *  \return QVariant : Contact's data associated with the role.
 ******************************************************************************/
QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    QVariant data;
    if(index.isValid() && index.row() < m_data.count()) {
        Contact* contact = m_data.at(index.row());
        if(contact) {
            switch(role) {
            case CONTACT_ID:
                data = contact->contactID();
                break;
            case CONTACT_NAME:
                data = contact->contactName();
                break;
            case CONTACT_PHONE_NUMBERS:
                //data = QVariant::fromValue<PhoneNumbers>(contact->contactNumbers());
                data = contact->contactNumbers();
                break;
            default:
                break;
            }
        }
    }
    return data;
}

//******************************************************************************
/*! \brief Returns the number of rows under the given parent.
 *
 *  \details For this model it returns number of Contact instances contained.
 *
 *  \author Mohita Gandotra
 *
 *  \return int : Number of Contact's instances managed by the model.
 ******************************************************************************/

int ContactsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}
} //namespace QSIP
