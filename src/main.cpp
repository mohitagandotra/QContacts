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
#include "contactsmodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


//******************************************************************************
/*! \brief Main function. Application entry point
 *
 *  \author Mohita Gandotra
 *
 *  \param[in] argc : Count of arguments.
 *  \param[in] argv : Argument values.
 *
 *  \return int : Application return code.
 ******************************************************************************/
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QSIP::ContactsModel contactsModel(&app);
    engine.rootContext()->setContextProperty("contactsModel", &contactsModel);

    QSIP::ContactsEnumerator enumerator(&contactsModel, &app);
    engine.rootContext()->setContextProperty("enumerator", &enumerator);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
