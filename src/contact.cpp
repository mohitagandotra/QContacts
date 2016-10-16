#include "contact.h"

namespace QSIP {

Contact::Contact(QString id, QString name, PhoneNumbers numbers, QObject *parent) : QObject(parent),
    m_id(id),
    m_name(name),
    m_phoneNumbers(numbers)
{

}

void Contact::setContactName(const QString& newName)
{
    if (m_name.compare(newName) != 0) {
        m_name = newName;
        emit contactNameChanged();
    }
}

PhoneNumbers Contact::contactNumbers() const
{
    return m_phoneNumbers;
}

} // QSIP
