//
//  ViewController.m
//  ios_test
//
//  Created by John on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

#import <gToolsP/gTimeP.h>

#import "TimeListViewController.h"

@interface TimeListViewController ()

@end

@implementation TimeListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    gzy::gStringList tmpList;
    gTimeP::Instance()->GetCurList(tmpList);
    gString tmpStr;
    
    gForeach(tmpList.cbegin(), tmpList.cend(), [&tmpStr](const gString &x){
        if (x.empty())
        {
            tmpStr += "\n";
        }
        else
        {
            tmpStr += x + "\n";
        }
    });
    
    for (UITextView *subView in self.view.subviews)
    {
        if ([subView isKindOfClass:[UITextView class]])
        {
            subView.text = [NSString stringWithCString:tmpStr.c_str() encoding:[NSString defaultCStringEncoding]];
        }
    }
}


@end
