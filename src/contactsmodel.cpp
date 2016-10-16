#include "contactsmodel.h"
#include "contact.h"

namespace QSIP {

ContactsModel::ContactsModel(QObject *parent) : QAbstractListModel(parent)
{

}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CONTACT_ID] = "contact_id";
    roles[CONTACT_NAME] = "contact_name";
    roles[CONTACT_IMAGE] = "contact_image";
    roles[CONTACT_PHONE_NUMBERS] = "contact_phone_numbers";
    return roles;
}

void ContactsModel::addContact(QString contactID, QString name, PhoneNumbers phoneNumbers)
{
    beginInsertRows(QModelIndex(),m_data.count(),m_data.count());
    m_data.append(new Contact(contactID, name, phoneNumbers, this));
    endInsertRows();
}

void ContactsModel::clear()
{
    beginResetModel();
    foreach(Contact* contact, m_data)
        delete contact;
    m_data.clear();
    endResetModel();
}

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

int ContactsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}
} //namespace QSIP
