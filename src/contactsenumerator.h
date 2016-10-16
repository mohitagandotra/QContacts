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
#ifndef CONTACTSENUMERATOR_H
#define CONTACTSENUMERATOR_H

#include <QObject>

namespace QSIP {
// Forward declerations
class ContactsModel;

//******************************************************************************
/*! \brief Helper class to fetch contacts from underlying OS.
 *
 *  \author Mohita Gandotra
 ******************************************************************************/
class ContactsEnumerator : public QObject
{
    Q_OBJECT
public:
    explicit ContactsEnumerator(ContactsModel* model, QObject *parent = 0);
signals:

public slots:
    void fetchContacts();

private:
    ContactsModel* m_model;
};

} // namespace QSIP

#endif // CONTACTSENUMERATOR_H
