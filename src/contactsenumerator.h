#ifndef CONTACTSENUMERATOR_H
#define CONTACTSENUMERATOR_H

#include <QObject>

namespace QSIP {

class ContactsModel;
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
