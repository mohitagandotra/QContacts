#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <types.h>
#include <QAbstractListModel>

namespace QSIP {

class Contact;
class ContactsModel : public QAbstractListModel
{
    Q_OBJECT
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
