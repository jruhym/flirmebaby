//
//  FLIROneSDKVideoRendererDelegate.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 9/17/14.
//  Copyright (c) 2014 flir. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>

/**
 The video renderer delegate can be used to allow users to render frames of a video their own way, using the image format of their choice rather than the default MSX.
 
 By default, the stream manager will record video in the current palette as MSX video, regardless of the formats being streamed.
 */
@protocol FLIROneSDKVideoRendererDelegate <NSObject>

/**
 When specified, allows the user to render a custom UIImage to be used in the recording video at the given timestamp
 @param timestamp The timestamp at which this UIImage will be used in the video
 @return A UIImage to be written to video at the given timestamp
 */
- (UIImage *) imageForFrameAtTimestamp:(CMTime)timestamp;


@end