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
#ifndef CONTACT_H
#define CONTACT_H

#include "types.h"
#include <QObject>
#include <QHash>
#include <QPair>

namespace QSIP {

//******************************************************************************
/*! \brief Defines a Contact with properties like, id, name, PhoneNumbers.
 *
 *  \author Mohita Gandotra
 ******************************************************************************/
class Contact : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString contactID READ contactID)
    Q_PROPERTY(QString contactName READ contactName WRITE setContactName NOTIFY contactChanged)

public:
    explicit Contact(QString id, QString name, PhoneNumbers numbers, QObject *parent = 0);

public:
    //! Returns the contact id of the contact.
    QString contactID() const { return m_id; }

    //! Returns the contact name of the contact.
    QString contactName() const { return m_name; }
    void setContactName(const QString &newName);
    PhoneNumbers contactNumbers() const;

signals:
    //! Emitted when contact data is changed.
    void contactChanged();

private:
    QString m_id;
    QString m_name;
    PhoneNumbers m_phoneNumbers;
};

} // namespace QSIP
#endif // CONTACT_H
