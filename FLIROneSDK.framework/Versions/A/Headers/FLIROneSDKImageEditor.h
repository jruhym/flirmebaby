//
//  FLIROneSDKImageEditor.h
//  FLIROneSDK
//
//  Created by Sean Burau on 5/20/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <FLIROneSDK/FLIROneSDKDelegateManager.h>
#import <FLIROneSDK/FLIROneSDKImagePropertyController.h>
#import <FLIROneSDK/FLIROneSDKImageEditorDelegate.h>
#import <FLIROneSDK/FLIROneSDKImageReceiverDelegate.h>

/**
 Used to load, manipulate, display, and save captured images.
 You can save images to the library using the [FLIROneSDKStreamManager capturePhoto] method. This class can only be used to edit photos captured by the FLIROneSDKStreamManager.
 
 The workflow for this class is as follows:
 
    1. loadImageWithFilepath
 
    2. Perform any editing methods such as setPalette:
 
    3. finishEditingAndSaveCurrentImageToFilepath:withPreviewImage:
 
 The features implemented in this class are included in the edit feature of the prebuilt UI FLIROneSDKLibraryViewController included in the SDK
 
 @note This class is thread safe; you may call any method from any thread
 without issue.
 
 @warning Do not attempt to create another instance of this class. Always
 use the sharedInstance class method to retrieve the global singleton.
 */
@interface FLIROneSDKImageEditor : NSObject <FLIROneSDKImagePropertyController>

/**---------------------------------------------------------------------------------------
 * @name Accessing the FLIROneSDKImageEditor sharedInstance
 *  ---------------------------------------------------------------------------------------
 */
/**Accesses and returns a reference to the global singleton instance. If a singleton has not been initialized yet, it will initialize the singleton instance.
 
 The FLIROneSDKImageEditor is exclusively accessed via a reference to the singleton instance. All of the instance methods will be called on this singleton object.
 
 @return A reference to the global singleton instance.
 */
+ (instancetype)sharedInstance;

/**---------------------------------------------------------------------------------------
 * @name Adding and Removing Delegates
 *  ---------------------------------------------------------------------------------------
 */

/**Register a new delegate for FLIR ONE events. If the delegate has already been added previously, this method will have no effect.
 
 As an example to register the current view controller as a FLIROneSDKDelegate:
 
 [FLIROneSDK sharedInstance] addDelegate:self];
 
 @param delegate The object to register for FLIR ONE callback events.
 */
- (void) addDelegate:(id <FLIROneSDKImageEditorDelegate, FLIROneSDKImageReceiverDelegate>) delegate;

/**
 Unsubscribe an object that was previously registered with addDelegate from receiving FLIR ONE events.
 If the delegate was not been previously added, this method will have no effect.
 
 @param delegate The object to unsubscribe from FLIR ONE callback events
 */
- (void) removeDelegate:(id <FLIROneSDKImageEditorDelegate, FLIROneSDKImageReceiverDelegate>) delegate;

/**---------------------------------------------------------------------------------------
 * @name Loading and Saving an Image
 *  ---------------------------------------------------------------------------------------
 */
/**
 Loads an image with the specified filename from the on-disk library into the editor.
 Every call to this method will result in the FLIROneSDKEditorImageDidFinishLoading
 callback being triggered for all registered delegates.
 
 @param filepath The filepath location to load the image from
 
 @note If you simply need to retrieve a thumbnail for a file, use the FLIROneSDKLibraryManager's
 thumbnailForFilename method.
 
 @see finishEditingAndSaveCurrentImageToFilepath:withPreviewImage:
 @see [FLIROneSDKStreamManager capturePhotoWithFilepath:]
 @see FLIROneSDKLibraryManager
 @see [FLIROneSDKLibraryManager thumbnailForFilepath:]
 */

- (void) loadImageWithFilepath:(NSURL *)filepath;

/**
 Refresh the loaded image using the imageOptions property of the image editor
 
 This will trigger callbacks for all associated data.
 @see [FLIROneSDKImagePropertyController imageOptions]
 */
- (void)refreshCurrentImageWithCurrentImageOptions;

/**
 Saves the current image being edited to the library on disk.
 Every call to this method will result in the FLIROneSDKEditorImageDidFinishSaving
 callback being triggered for all registered delegates. Also, following this method further editing cannot be performed until a new image is loaded using loadImageWithFilepath:
 
 @param filepath The filepath where the image should be saved. In order to save in-place, specify the filepath used to load the image originally
 
 @param previewImage The preview image to use with the JPEG's dipslay image and thumbnail file
 
 @see loadImageWithFilepath:
 @see FLIROneSDKLibraryManager
 */

- (void)finishEditingAndSaveCurrentImageToFilepath:(NSURL *)filepath withPreviewImage:(UIImage *)previewImage;

@end
