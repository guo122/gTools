//====================================================================
//  ODPNotification.h
//  created 7.8.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODPNOTIFICATION_H_40AFBC979A54EFC0F99D0841945BCFF0_
#define _ODPNOTIFICATION_H_40AFBC979A54EFC0F99D0841945BCFF0_

// Qt lib import
#include <QString>
#include <QDateTime>

namespace ODNotification_iOS
{
#ifdef Q_OS_IOS

void pushNotifiction(const QString &message, const QDateTime &dateTime);

void cancelAllNotifictions(void);
#endif
}

#endif // _ODPNOTIFICATION_H_40AFBC979A54EFC0F99D0841945BCFF0_
