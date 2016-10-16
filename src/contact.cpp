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
#include "contact.h"

namespace QSIP {

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Mohita Gandotra.
 *
 *  \param[in] id : Unique identifier of the contact.
 *  \param[in] name : Name of the contact.
 *  \param[in] numbers : Stringlist of phone numbers. [label_phno_1, phno_1, label_phno_2, phno_2...].
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
Contact::Contact(QString id, QString name, PhoneNumbers numbers, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_name(name),
    m_phoneNumbers(numbers)
{

}

//******************************************************************************
/*! \brief Setter method to change the contact's name. The name is not changed
 *  in underlying OS contacts.
 *
 *  \author Mohita Gandotra.
 *
 *  \param[in] newName : New name of the contact.
 ******************************************************************************/
void Contact::setContactName(const QString& newName)
{
    if (m_name.compare(newName) != 0) {
        m_name = newName;
        emit contactChanged();
    }
}

//******************************************************************************
/*! \brief Returns list of phone numbers.
 *
 *  \author Mohita Gandotra.
 *
 *  \return PhoneNumbers : List of phone numbers in the format
 *  [label_phno_1, phno_1, label_phno_2, phno_2...].
 ******************************************************************************/
PhoneNumbers Contact::contactNumbers() const
{
    return m_phoneNumbers;
}

} // QSIP
