#import "ioscontacthandler.h"
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
