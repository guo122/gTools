//
//  AppDelegate.m
//  gBrick
//
//  Created by guo122 on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)runUserThread:(NSDictionary *)launchOptions {
    while (true) {
        usleep(100000);
        NSLog(@"Tick...");
    }
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    self.window = [[UIWindow alloc]initWithFrame:
                   [[UIScreen mainScreen]bounds]];
    self.window.backgroundColor = [UIColor whiteColor];
    
    self.vc = [[GViewController alloc]init];
    UINavigationController *nav = [[UINavigationController alloc]initWithRootViewController:self.vc];
    [nav setNavigationBarHidden:YES animated:YES];
    
    [self.window setRootViewController:nav];
    [self.window makeKeyAndVisible];
    
    NSThread* thread = [[NSThread alloc] initWithTarget:self selector:@selector(runUserThread:) object:launchOptions];
    [thread setStackSize:8 * 1024 * 1024];
    [thread start];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

+ (AppDelegate*)Instance
{
    return (AppDelegate*)[UIApplication sharedApplication].delegate;
}

@end
