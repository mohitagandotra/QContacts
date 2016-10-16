#include "contactsenumerator.h"
#include "contactsmodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //qmlRegisterUncreatableType<QSIP::ContactsModel>("com.qsip.qmlcomponents", 1, 0, "ContactsModel","");

    QSIP::ContactsModel contactsModel(&app);
    engine.rootContext()->setContextProperty("contactsModel", &contactsModel);

    QSIP::ContactsEnumerator enumerator(&contactsModel, &app);
    engine.rootContext()->setContextProperty("enumerator", &enumerator);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
