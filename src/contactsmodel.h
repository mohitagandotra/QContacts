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
#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <types.h>
#include <QAbstractListModel>

namespace QSIP {
// Forward decleration.
class Contact;

//******************************************************************************
/*! \brief Model class for Contacts Data. Apply a filter model to sort or filter the contacts.
 *
 *  \author Mohita Gandotra
 ******************************************************************************/
class ContactsModel : public QAbstractListModel
{
    Q_OBJECT

    //******************************************************************************
    /*! \brief Models roles for Contacts data.
     *
     *  \author Mohita Gandotra
     ******************************************************************************/
    enum ExtraRoles {
        CONTACT_ID = Qt::UserRole+1,
        CONTACT_NAME,
        CONTACT_IMAGE,
        CONTACT_PHONE_NUMBERS
    };

public:
    explicit ContactsModel(QObject *parent = 0);

// QAbstarctItemModel Implementation.
public:
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int,QByteArray> roleNames() const override;

public:
    void addContact(QString contactID, QString name, PhoneNumbers phoneNumbers);
    void clear();

signals:

public slots:

private:
    QList<Contact*> m_data;
};

} // namespace QSIP
#endif // CONTACTSMODEL_H
