//
//  FLIROneSDKImageEditorDelegate.h
//  FLIROneSDK
//
//  Created by Sean Burau on 9/16/14.
//  Copyright (c) 2014 flir. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FLIROneSDK/FLIROneSDKImageReceiverDelegate.h>

/**
  The Image Editor uses this protocol to communicate to its delegates and inform them of image loading success or failure, and image saving success or failure
 */

@protocol FLIROneSDKImageEditorDelegate <FLIROneSDKImageReceiverDelegate, NSObject>

@optional

/**---------------------------------------------------------------------------------------
 * @name FLIROneSDKImageEditor Events
 *  ---------------------------------------------------------------------------------------
 */
/**
 Triggered after an image is loaded into the editor via a FLIROneSDKImageEditor loadImageFromLibraryWithFilename: request.
 This event will always trigger after calling loadImageFromLibraryWithFilename.
 
 @param loadedStatus Whether or not the image was successfully loaded. If the image was loaded successfully,
 the FLIROneSDKEditorImageDidChange callback is trigger immediately after with the initial image.
 
 @see FLIROneSDKImageIOStatus
 @see FLIROneSDKImageEditor
 
 */
- (void) FLIROneSDKEditorImageDidFinishLoading:(FLIROneSDKImageIOStatus)loadedStatus;

/**
 Triggered after a FLIROneSDKImageEditor finishEditingAndSaveCurrentImageToFilepath:withPreviewImage: request.
 This event will always trigger after calling finishEditingAndSaveCurrentImageToFilepath:withPreviewImage:.
 
 @param savedStatus Whether or not the image was successfully saved.
 
 @param filepath The filepath of the saved image
 */

- (void) FLIROneSDKEditorImageDidFinishSaving:(FLIROneSDKImageIOStatus)savedStatus withFilepath:(NSURL *)filepath;


@end
