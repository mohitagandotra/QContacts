#include "ioscontacts.h"
#include <QString>
#import <Foundation/NSArray.h>
#import <Foundation/NSObject.h>
#import <Contacts/Contacts.h>


@interface ContactsScan:NSObject
{
    QSIP::IosContacts *m_handler;
}
- (ContactsScan*) init: (QSIP::IosContacts *)handler;
- (void) contactScan;
- (void) getAllContact;
- (void) parseContactWithContact :(CNContact* )contact;
- (NSMutableArray *) parseAddressWithContac: (CNContact *)contact;
@end


@implementation ContactsScan


- (ContactsScan*) init: (QSIP::IosContacts*)handler
{
    m_handler = handler;
    return self;
}

- (void) contactScan
{
    if ([CNContactStore class]) {
        //ios9 or later
        CNEntityType entityType = CNEntityTypeContacts;
        if( [CNContactStore authorizationStatusForEntityType:entityType] == CNAuthorizationStatusNotDetermined)
         {
             CNContactStore * contactStore = [[CNContactStore alloc] init];
             [contactStore requestAccessForEntityType:entityType completionHandler:^(BOOL granted, NSError * _Nullable error) {
                 if (granted == YES){
                     [self getAllContact];
                 }
             }];
         }
        else if( [CNContactStore authorizationStatusForEntityType:entityType]== CNAuthorizationStatusAuthorized)
        {
            [self getAllContact];
        }
    }
}

-(void)getAllContact
{
    if([CNContactStore class])
    {
        //iOS 9 or later
        NSError* contactError;
        CNContactStore* addressBook = [[CNContactStore alloc]init];
        [addressBook containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers: @[addressBook.defaultContainerIdentifier]] error:&contactError];
        NSArray * keysToFetch =@[CNContactEmailAddressesKey, CNContactPhoneNumbersKey, CNContactFamilyNameKey, CNContactGivenNameKey, CNContactPostalAddressesKey];
        CNContactFetchRequest * request = [[CNContactFetchRequest alloc]initWithKeysToFetch:keysToFetch];
        BOOL success = [addressBook enumerateContactsWithFetchRequest:request error:&contactError usingBlock:^(CNContact * __nonnull contact, BOOL * __nonnull stop){
            [self parseContactWithContact:contact];
        }];
        if (contactError) {
            NSLog(@"error fetching contacts %@", contactError);
        }
    }
}

- (void)parseContactWithContact :(CNContact* )contact
{
    NSString *identifier = contact.identifier;
    NSString *firstName =  contact.givenName;
    NSString *lastName =  contact.familyName;

    NSArray<CNLabeledValue<CNPhoneNumber *> *> *phNos= contact.phoneNumbers;
    QSIP::PhoneNumbers phoneNumbers;
    for (id object in phNos) {
        NSString* label = [object label];
        label = [CNLabeledValue localizedStringForLabel:label];
        NSString* number = [[object value] stringValue];
        if (label && number) {
            phoneNumbers<<QString::fromNSString(label)<<QString::fromNSString(number);
        }
    }
    //NSString * phone = [[contact.phoneNumbers valueForKey:@"value"] valueForKey:@"digits"];
    //NSString * email = [contact.emailAddresses valueForKey:@"value"];
    //NSArray * addrArr = [self parseAddressWithContac:contact];

    QString name = QString("%1 %2")
            .arg(QString::fromNSString(firstName))
            .arg(QString::fromNSString(lastName));
    // Emit contact data to recieve it on the Qt thread.
    m_handler->newContact(QString::fromNSString(identifier), name, phoneNumbers);
}

- (NSMutableArray *)parseAddressWithContac: (CNContact *)contact
{
    NSMutableArray * addrArr = [[NSMutableArray alloc]init];
    CNPostalAddressFormatter * formatter = [[CNPostalAddressFormatter alloc]init];
    NSArray * addresses = (NSArray*)[contact.postalAddresses valueForKey:@"value"];
    if (addresses.count > 0) {
        for (CNPostalAddress* address in addresses) {
            [addrArr addObject:[formatter stringFromPostalAddress:address]];
        }
    }
    return addrArr;
}

@end


namespace QSIP {

class IosContactsPrivate
{
private:
     IosContactsPrivate(IosContacts* parentInstance);
    ~IosContactsPrivate();

     void fetchContacts();

private:
     IosContacts* parent;
     ContactsScan *scanner;
     friend class IosContacts;
};

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Mohita Gandotra.
 *
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
IosContacts::IosContacts(QObject *parent):
    QObject(parent)
{
    d = new IosContactsPrivate(this);
}

IosContacts::~IosContacts()
{
    delete d;
}

//******************************************************************************
/*! \brief Fetch contacts from iOS.
 *
 *  \author Mohita Gandotra.
 ******************************************************************************/
void IosContacts::fetchContacts()
{
    d->fetchContacts();
}

IosContactsPrivate::IosContactsPrivate(IosContacts *parentInstance):
    parent(parentInstance)
{
    scanner = [[ContactsScan alloc] init:parent];
}

IosContactsPrivate::~IosContactsPrivate()
{
    [scanner release];
}

void IosContactsPrivate::fetchContacts()
{
    [scanner contactScan];
}

} // namespace QSIP
