//
//  FLIROneSDKImageMetadata.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 9/17/14.
//  Copyright (c) 2014 flir. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FLIROneSDK/FLIROneSDKPalette.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 FLIROneSDKImageMetadata describes the state of the stream or image editor, including current palette and emissivity.
 */

@interface FLIROneSDKImageMetadata : NSObject

/**
 Palette associated with this image/frame
 */
@property (strong, nonatomic, readonly) FLIROneSDKPalette *palette;
/**
 Emissivity of current image/frame
 */
@property (nonatomic, readonly) CGFloat emissivity;

@end
