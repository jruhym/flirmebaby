//
//  FLIROneSDKImageReceiverDelegate.h
//  FLIROneSDK
//
//  Created by Sean Burau on 9/16/14.
//  Copyright (c) 2014 flir. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <FLIROneSDK/FLIROneSDKTypes.h>
#import <FLIROneSDK/FLIROneSDKPalette.h>
#import <FLIROneSDK/FLIROneSDKImageMetadata.h>
#import <FLIROneSDK/FLIROneSDKDelegateManager.h>

/**
 The image receiver delegate allows users to receive live frames from the camera in the image formats of their choice, or to load receive images generated from a file on disk in the same formats.
 
 When receiving data in a given format, it can be rendered into a UIImage using the FLIROneSDKUIImage class.
 
 @see [FLIROneSDKUIImage imageWithFormat:andData:andSize:]
 */

@protocol FLIROneSDKImageReceiverDelegate <NSObject>

@optional

/**
 Called whenever a frame is delivered to the delegate by stream manager, or whenever an image is loaded by the image editor
 
 @param delegateManager The delegate manager, either FLIROneSDKStreamManager or FLIROneSDKImageEditor
 @param options A bitmask of options relating to the data being returned
 @param metadata Metadata regarding the particular frame being delivered, such as palette used, emissivity, etc
 */

- (void) FLIROneSDKDelegateManager:(NSObject *)delegateManager didReceiveFrameWithOptions:(FLIROneSDKImageOptions)options metadata:(FLIROneSDKImageMetadata *)metadata;

/**
 Called when the user has requested the MSX (thermal + visual) image format
 
 @param delegateManager The delegate manager, either FLIROneSDKStreamManager or FLIROneSDKImageEditor
 @param msxImage The data formatted in FLIROneSDKThermalRGBA8888 format
 @param size The size of the data, used for rendering
 
 @warning The size parameter is guaranteed to be static per-session, but changing FLIR One devices may alter the size parameter
 @see FLIROneSDKUIImage
 */
- (void) FLIROneSDKDelegateManager:(NSObject *)delegateManager didReceiveBlendedMSXRGBA8888Image:(NSData *)msxImage imageSize:(CGSize)size;

/**
 Called when the user has requested the 14 bit linear flux data
 
 @param delegateManager The delegate manager, either FLIROneSDKStreamManager or FLIROneSDKImageEditor
 @param linearFluxImage The data of the image
 @param size The size of the data, used for rendering
 
 @warning The size parameter is guaranteed to be static per-session, but changing FLIR One devices may alter the size parameter
 @see FLIROneSDKUIImage
 */
- (void) FLIROneSDKDelegateManager:(NSObject *)delegateManager didReceiveThermal14BitLinearFluxImage:(NSData *)linearFluxImage imageSize:(CGSize)size;
/**
 Called when the user has requested the pure thermal image format
 
 @param delegateManager The delegate manager, either FLIROneSDKStreamManager or FLIROneSDKImageEditor
 @param thermalImage The data of the image
 @param size The size of the data, used for rendering
 
 @warning The size parameter is guaranteed to be static per-session, but changing FLIR One devices may alter the size parameter
 @see FLIROneSDKUIImage
 */
- (void) FLIROneSDKDelegateManager:(NSObject *)delegateManager didReceiveThermalRGBA8888Image:(NSData *)thermalImage imageSize:(CGSize)size;
/**
 Called when the user has requested the visual image formatted with JPEG
 
 @param delegateManager The delegate manager, either FLIROneSDKStreamManager or FLIROneSDKImageEditor
 @param visualJPEGImage The data of the image
 
 @see FLIROneSDKUIImage
 */
- (void) FLIROneSDKDelegateManager:(NSObject *)delegateManager didReceiveVisualJPEGImage:(NSData *)visualJPEGImage;
/**
 Called when the user has requested the visual image formatted with YCbCr
 
 @param delegateManager The delegate manager, either FLIROneSDKStreamManager or FLIROneSDKImageEditor
 @param visualYCbCr888Image The data of the image
 @param size The size of the data, used for rendering
 
 @warning The size parameter is guaranteed to be static per-session, but changing FLIR One devices may alter the size parameter
 @see FLIROneSDKUIImage
 */
- (void) FLIROneSDKDelegateManager:(NSObject *)delegateManager didReceiveVisualYCbCr888Image:(NSData *)visualYCbCr888Image imageSize:(CGSize)size;

/**
 Returned when the user has requested radiometric data, once per image load or once per frame delivered by stream manager
 
 @param delegateManager The delegate manager, either FLIROneSDKStreamManager or FLIROneSDKImageEditor
 @param radiometricData An array of radiometric data where each value is equal to the temperature in kelvin at a location in the frame
 @param size The size of the data array
 
 @warning The size parameter is guaranteed to be static per-session, but changing FLIR One devices may alter the size parameter
 
 */
- (void) FLIROneSDKDelegateManager:(NSObject *)delegateManager didReceiveRadiometricData:(NSData *)radiometricData imageSize:(CGSize)size;

@end
