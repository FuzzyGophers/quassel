// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "clientsettings.h"
#include "osxnotificationbackend.h"

#include <QCheckBox>
#include <QHBoxLayout>

#import <UserNotifications/UserNotifications.h>

@interface QuasselNotificationDelegate : NSObject <UNUserNotificationCenterDelegate>
@end

@implementation QuasselNotificationDelegate
- (void)userNotificationCenter:(UNUserNotificationCenter *)center
       didReceiveNotificationResponse:(UNNotificationResponse *)response
                withCompletionHandler:(void (^)(void))completionHandler
{
    // Handle notification response if needed (e.g., activate Quassel when clicked)
    completionHandler();
}
@end

namespace {

void SendNotificationCenterMessage(NSString* title, NSString* subtitle) {
    UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    
    // Request authorization for notifications
    [center requestAuthorizationWithOptions:(UNAuthorizationOptionAlert | UNAuthorizationOptionSound)
                         completionHandler:^(BOOL granted, NSError * _Nullable error) {
        if (!granted) {
            NSLog(@"Notification authorization denied: %@", error.localizedDescription);
            return;
        }
        
        // Create notification content
        UNMutableNotificationContent *content = [[UNMutableNotificationContent alloc] init];
        [content setTitle:title];
        [content setSubtitle:subtitle];
        [content setSound:[UNNotificationSound defaultSound]];
        
        // Create a unique request identifier
        NSString *identifier = [NSString stringWithFormat:@"QuasselNotification-%f", [[NSDate date] timeIntervalSince1970]];
        
        // Create the notification request
        UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:identifier
                                                                            content:content
                                                                            trigger:nil];
        
        // Deliver the notification
        [center addNotificationRequest:request withCompletionHandler:^(NSError * _Nullable error) {
            if (error) {
                NSLog(@"Failed to deliver notification: %@", error.localizedDescription);
            }
            [content release];
        }];
    }];
}

}

OSXNotificationBackend::OSXNotificationBackend(QObject *parent)
    : AbstractNotificationBackend(parent),
      _enabled(true)
{
    NotificationSettings notificationSettings;
    notificationSettings.initAndNotify("OSXNotification/Enabled", this, &OSXNotificationBackend::enabledChanged, true);
    
    // Set up the notification delegate
    UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    center.delegate = [[QuasselNotificationDelegate alloc] init];
}

OSXNotificationBackend::~OSXNotificationBackend()
{
    // Clean up the delegate
    UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    if (center.delegate) {
        [center.delegate release];
        center.delegate = nil;
    }
}

void OSXNotificationBackend::enabledChanged(const QVariant &value)
{
    _enabled = value.toBool();
}

void OSXNotificationBackend::notify(const Notification &notification)
{
    if (!_enabled)
    {
        return;
    }

    // Convert QString to NSString
    NSString *message = [[NSString alloc] initWithUTF8String:notification.sender.toUtf8().constData()];
    NSString *summary = [[NSString alloc] initWithUTF8String:notification.message.toUtf8().constData()];
    
    SendNotificationCenterMessage(message, summary);
    
    [message release];
    [summary release];
}

void OSXNotificationBackend::close(uint /*notificationId*/)
{
    // Optionally implement closing notifications if needed
    // UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    // [center removeDeliveredNotificationsWithIdentifiers:@[identifier]];
}

SettingsPage *OSXNotificationBackend::createConfigWidget() const
{
    return new ConfigWidget();
}

OSXNotificationBackend::ConfigWidget::ConfigWidget(QWidget *parent)
    : SettingsPage("Internal", "OSXNotification", parent)
{
    _enabledBox = new QCheckBox(tr("Show macOS notifications"));
    connect(_enabledBox, &QCheckBox::toggled, this, &ConfigWidget::widgetChanged);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_enabledBox);
}

void OSXNotificationBackend::ConfigWidget::widgetChanged()
{
    bool changed = (_enabled != _enabledBox->isChecked());
    if (changed != hasChanged())
        setChangedState(changed);
}

bool OSXNotificationBackend::ConfigWidget::hasDefaults() const
{
    return true;
}

void OSXNotificationBackend::ConfigWidget::defaults()
{
    _enabledBox->setChecked(true);
    widgetChanged();
}

void OSXNotificationBackend::ConfigWidget::load()
{
    NotificationSettings s;
    _enabled = s.value("OSXNotification/Enabled", false).toBool();
    _enabledBox->setChecked(_enabled);
    setChangedState(false);
}

void OSXNotificationBackend::ConfigWidget::save()
{
    NotificationSettings s;
    s.setValue("OSXNotification/Enabled", _enabledBox->isChecked());
    load();
}
