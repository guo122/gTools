//
//  gViewController.m
//  gBrick
//
//  Created by guo122 on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

@import MetalKit;

#import "MtkController.h"

#import "gViewController.h"

@interface GViewController ()

@property (weak, nonatomic) IBOutlet MtkController *MtkMap;

@property float count;

@end

@implementation GViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSLog(@"[init] MapViewController init.");
    
    self.count = 0.5;
    [self.MtkMap Init:self];

    for (int i = 0; i < 1; i++ )
    {
        CGRect tmpRect;
        tmpRect.origin.x = self.count;
        tmpRect.origin.y = self.count;
        tmpRect.size.height = 0.1;
        tmpRect.size.width = 0.1;

        vector_uint4 tmpC = {1.0, 1.0, 1.0, 1.0};

        [self.MtkMap DrawRect:tmpRect :tmpC ];

        self.count += 0.1;
    }


}

@end
