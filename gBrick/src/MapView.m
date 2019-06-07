//
//  MapView.m
//  gBrick
//
//  Created by guo122 on 2019/6/7.
//  Copyright © 2019 John. All rights reserved.
//


#import "MapView.h"

@interface MapView ()

@property (nonatomic) NSMutableArray* touches;

@end

@implementation MapView

////////////////////////////////////////////////////////////
- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch* touch in touches)
    {
        // find an empty slot for the new touch
        NSUInteger index = [self.touches indexOfObject:[NSNull null]];
        if (index != NSNotFound)
        {
            [self.touches replaceObjectAtIndex:index withObject:touch];
        }
        else
        {
            [self.touches addObject:touch];
            index = [self.touches count] - 1;
        }
        
        // get the touch position
        CGPoint point = [touch locationInView:self];
        
        NSLog(@"[touch] begin: [%i], %f, %f", index, point.x, point.y);
//        sf::Vector2i position(static_cast<int>(point.x), static_cast<int>(point.y));
//
//        // notify the application delegate
//        [[SFAppDelegate getInstance] notifyTouchBegin:index atPosition:position];
    }
}


////////////////////////////////////////////////////////////
- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch* touch in touches)
    {
        // find the touch
        NSUInteger index = [self.touches indexOfObject:touch];
        if (index != NSNotFound)
        {
            // get the touch position
            CGPoint point = [touch locationInView:self];
            
            NSLog(@"[touch] move: [%i], %f, %f", index, point.x, point.y);
//            sf::Vector2i position(static_cast<int>(point.x), static_cast<int>(point.y));
//
//            // notify the application delegate
//            [[SFAppDelegate getInstance] notifyTouchMove:index atPosition:position];
        }
    }
}


////////////////////////////////////////////////////////////
- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch* touch in touches)
    {
        // find the touch
        NSUInteger index = [self.touches indexOfObject:touch];
        if (index != NSNotFound)
        {
            // get the touch position
            CGPoint point = [touch locationInView:self];
            
            NSLog(@"[touch] end: [%i], %f, %f", index, point.x, point.y);
//            sf::Vector2i position(static_cast<int>(point.x), static_cast<int>(point.y));
//
//            // notify the application delegate
//            [[SFAppDelegate getInstance] notifyTouchEnd:index atPosition:position];
            
            // remove the touch
            [self.touches replaceObjectAtIndex:index withObject:[NSNull null]];
        }
    }
}


////////////////////////////////////////////////////////////
- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    // Treat touch cancel events the same way as touch end
    [self touchesEnded:touches withEvent:event];
}

@end
