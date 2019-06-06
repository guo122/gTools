//
//  MtkController.h
//  gBrick
//
//  Created by guo122 on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

@import MetalKit;

@interface MtkController : MTKView <MTKViewDelegate>

-(void) Init: (UIViewController*)ViewController;

-(void) DrawRect: (CGRect)bounds;

@end

