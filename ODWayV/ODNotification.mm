//====================================================================
//  ODPNotification.mm
//  created 7.8.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODNotification.h"

#ifdef Q_OS_IOS

// iOS lib import
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

void ODNotification_iOS::pushNotifiction(const QString &message, const QDateTime &dateTime)
{
    UIUserNotificationType types = UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIRemoteNotificationTypeSound;

    UIUserNotificationSettings *setting = [UIUserNotificationSettings settingsForTypes:types categories:NULL];

    [[UIApplication sharedApplication] registerUserNotificationSettings:setting];

    NSDateComponents *dateComp = [[NSDateComponents alloc] init];
    dateComp.year = dateTime.date().year();
    dateComp.month = dateTime.date().month();
    dateComp.day = dateTime.date().day();
    dateComp.hour = dateTime.time().hour();
    dateComp.minute = dateTime.time().minute();
    dateComp.second = dateTime.time().second();
    dateComp.timeZone = [NSTimeZone systemTimeZone];

    NSCalendar *calendar = [NSCalendar calendarWithIdentifier:NSGregorianCalendar];

    NSDate *date = [calendar dateFromComponents:dateComp];

    UILocalNotification *notifiction = [[UILocalNotification alloc]init];
    notifiction.alertBody = [NSString stringWithFormat:@"%s" , message.toStdString().c_str()];
    notifiction.fireDate = date;
    notifiction.soundName = UILocalNotificationDefaultSoundName;
//    notifiction.applicationIconBadgeNumber = 0;

    [[UIApplication sharedApplication]scheduleLocalNotification:notifiction];

}

void ODNotification_iOS::cancelAllNotifictions(void)
{
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber: 0];
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
}

#endif
