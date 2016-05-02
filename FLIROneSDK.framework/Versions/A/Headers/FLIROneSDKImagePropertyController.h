//
//  FLIROneSDKImagePropertyController.h
//  FLIROneSDK
//
//  Created by Sean Burau on 9/16/14.
//  Copyright (c) 2014 flir. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <FLIROneSDK/FLIROneSDKPalette.h>
#import <FLIROneSDK/FLIROneSDKTypes.h>

/**
 Image Property Controller is a protocol which ImageEditor and StreamManager both conform to. It provides a uniform interface for setting palette, emissivity, and data format of the desired data.
 */

@protocol FLIROneSDKImagePropertyController <NSObject>

/**---------------------------------------------------------------------------------------
 * @name Image Properties
 *  ---------------------------------------------------------------------------------------
 */

/**
 The current FLIROneSDKPalette used to colorize the thermal component of the stream.
 You may read and write the value of this property from any thread safely.
 
 To update the current palette that incoming frames will be colorized with you must set the value of this property to a FLIROneSDKPalette. This should be done with the name of a palette from the palette list. For example:
 
 FLIROneSDKPalette *palette = [[FLIROneSDKPalette palettes] objectAtIndex:self.paletteCount];
 [[FLIROneSDKStreamManager sharedInstance] setCurrentPalette:palette];
 
 @note You may still change this property while recording a video.
 
 @see FLIROneSDKPalette
 */
@property (readwrite, nonatomic) FLIROneSDKPalette *palette;

/**
 The current emissivity used for the thermal component of the stream.
 You may read and write the value of this property from any thread safely.
 
 To update the current emissivity that incoming frames will be colorized with you must set the value of this property to a double, optionally using one of four preset values. For example:
 
 [[FLIROneSDKStreamManager sharedInstance] setEmissivity:FLIROneSDKEmissivityGlossy];
 
 @note You may still change this property while recording a video.
 
 */
@property (readwrite, nonatomic) CGFloat emissivity;

/**
 The image options dictate what formats are delivered from the sled during streaming or image editing.
 
 Specifying image options in the Stream Manager affects which callbacks you will receive on the next frame.
 @see [FLIROneSDKImageReceiverDelegate FLIROneSDKDelegateManager:didReceiveFrameWithOptions:metadata:];
 
 Specifying image options in the Image Editor affects which callbacks you will receive when refreshing the Image Editor with the current settings.
 @see [FLIROneSDKImageEditor refreshCurrentImageWithCurrentImageOptions];
 */
@property (readwrite, nonatomic) FLIROneSDKImageOptions imageOptions;

@end
