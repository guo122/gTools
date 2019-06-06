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

@end

@implementation MapViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.MtkMap Init:self];
}

- (IBAction)BtnMapAdd:(id)sender {
    NSLog(@"Map Add");
}
@end
