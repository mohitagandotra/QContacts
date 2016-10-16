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
#ifndef IOSCONTACTS_H
#define IOSCONTACTS_H

#include <QObject>
#include "types.h"

namespace QSIP {

//******************************************************************************
/*! \brief Helper class to getch contacts from iOS.
 *
 *  \author Mohita Gandotra
 ******************************************************************************/
class IosContacts : public QObject
{
    Q_OBJECT
public:
    IosContacts(QObject* parent=nullptr);

    void fetchContacts();

signals:
    // Emitted for every new contact.
    void newContact(QString id, QString name, QSIP::PhoneNumbers);
};

} // namespace QSIP
#endif // IOSCONTACTS_H
