TEMPLATE = app

QT += qml quick
android: QT += androidextras

CONFIG += c++11

RESOURCES += qml.qrc

OTHER_FILES =

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android {
DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/src/com/qsip/qcontacts/AndroidContacts.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

HEADERS += \
    contactsenumerator.h \
    contactsmodel.h \
    contact.h \
    types.h

ios {
HEADERS += \
    ios/ioscontacts.h

OBJECTIVE_SOURCES += \
    ios/ioscontacts.mm

LIBS += -framework CoreFoundation -framework Contacts
}

SOURCES += main.cpp \
    contactsenumerator.cpp \
    contactsmodel.cpp \
    contact.cpp



