#include "ioscontacthandler.h"
//#include "ios/ioscontacts.h"
#include <QString>
#import <Foundation/NSArray.h>
#import <Foundation/NSObject.h>
#import <Contacts/Contacts.h>


@interface ContactsScan:NSObject
{
    QSIP::IosContactHandler *m_handler;
}
- (ContactsScan*) init: (QSIP::IosContactHandler *)handler;
- (void) contactScan;
- (void) getAllContact;
- (void) parseContactWithContact :(CNContact* )contact;
- (NSMutableArray *) parseAddressWithContac: (CNContact *)contact;
@end


@implementation ContactsScan


- (ContactsScan*) init: (QSIP::IosContactHandler*)handler
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
                 if(granted){
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
    NSString * email = [contact.emailAddresses valueForKey:@"value"];
    NSArray * addrArr = [self parseAddressWithContac:contact];

    QString name = QString("%1 %2")
            .arg(QString::fromNSString(firstName))
            .arg(QString::fromNSString(lastName));
    m_handler->addNewContact(QString::fromNSString(identifier), name, phoneNumbers);
    //handler->onNewContact(QString::fromNSString(firstName) + " " + phoneNumber);
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

IosContactHandler::IosContactHandler()
{

}

IosContactHandler::~IosContactHandler()
{

}

void IosContactHandler::fetchContacts()
{
    ContactsScan *scanner = [[ContactsScan alloc] init:this];
    [scanner contactScan];
    [scanner release];
}

void IosContactHandler::addNewContact(QString id, QString name, QSIP::PhoneNumbers phNos)
{
    // Emit contact data to recieve it on the Qt thread.
    emit newContact(id, name, phNos);
}

} // namespace QSIP
