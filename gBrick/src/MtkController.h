//
//  MtkController.h
//  gBrick
//
//  Created by guo122 on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

@import MetalKit;

@interface MtkController : MTKView

-(void) Init: (UIViewController*)ViewController;

-(void) DrawRect: (CGRect)bounds :(vector_uint4)color;

-(vector_uint2) GetDrawableSize;

-(void) Render;

@end

