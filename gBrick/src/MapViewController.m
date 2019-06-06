//
//  MapViewController.m
//  gBrick
//
//  Created by guo122 on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

@import MetalKit;

#import "MtkController.h"

#import "MapViewController.h"

@interface MapViewController ()
- (IBAction)BtnMapAdd:(id)sender;

@property (strong, nonatomic) IBOutlet MtkController *MtkMap;

@property float count;

@end

@implementation MapViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.count = 0;
    [self.MtkMap Init:self];
}

- (IBAction)BtnMapAdd:(id)sender {
    NSLog(@"Map Add");
    vector_uint2 size = self.MtkMap.GetDrawableSize;
    NSLog(@"%i, %i", size[0], size[1]);
    
    CGRect tmpRect;
    tmpRect.origin.x = 0 + self.count;
    tmpRect.origin.y = 0 + self.count;
    tmpRect.size.height = 0.5;
    tmpRect.size.width = 0.5;
    
    vector_uint4 tmpC = {1.0, 1.0, 1.0, 1.0};
    
    [self.MtkMap DrawRect:tmpRect :tmpC ];
    
    self.count += 0.1;
}
@end
