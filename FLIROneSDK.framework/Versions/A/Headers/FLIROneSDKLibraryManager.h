//
//  FLIROneSDKLibraryManager.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 5/21/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// TODO: add documentation stating that thumbnail images are MSX blending of then-current palette
/**
 Manages images and videos that have been saved to disk via the
 FLIROneSDKStreamManager and FLIROneSDKImageEditor classes.
 
 @note This class can only manage photos and videos saved to disk via the FLIROneSDKStreamManager and FLIROneSDKImageEditor
 @warning You should use this class to remove files instead of doing so manually.
 @note You may choose to save images to any location in the file system, but any images saved in the media directory will be usable by the Library UI
 
 @warning Do not attempt to create another instance of this class. Always use the sharedInstance class method to retrieve the global singleton.
 
 @see [FLIROneSDKStreamManager startRecordingVideoWithFilepath:withVideoRendererDelegate:]
 @see [FLIROneSDKStreamManager capturePhotoWithFilepath:]
 @see [FLIROneSDKImageEditor loadImageWithFilepath:]
 */
@interface FLIROneSDKLibraryManager : NSObject

/**---------------------------------------------------------------------------------------
 * @name Accessing the FLIROneSDKLibraryManager sharedInstance
 *  ---------------------------------------------------------------------------------------
 */
/**Accesses and returns a reference to the global singleton instance. If a singleton has not been initialized yet, it will initialize the singleton instance.
 
 The FLIROneSDKLibraryManager is exclusively accessed via a reference to the singleton instance. All of the instance methods will be called on this singleton object.
 
 @return A reference to the global singleton instance.
 */
+ (instancetype)sharedInstance;

/**---------------------------------------------------------------------------------------
 * @name Other Methods
 *  ---------------------------------------------------------------------------------------
 */
/**
 Retrieves a thumbnail for a previously captured video or photo.
 
 @param filepath The filepath to retrieve the thumbnail for
 
 @return A UIImage representation of the file's thumbnail, or nil if the file does not exist.
 
 @see filepaths
 @see [FLIROneSDKStreamManager capturePhotoWithFilepath:]
 */
- (UIImage *) thumbnailForFilepath:(NSURL *)filepath;

/**
 Retrieves a preview image for a previously captured video.
 
 @param filepath The video filepath to retrieve the preview for
 
 @return A UIImage representation of the video's preview image, or nil if the video does not exist.
 
 @see filepaths
 @see [FLIROneSDKStreamManager startRecordingVideoWithFilepath:withVideoRendererDelegate:]
 */
- (UIImage *) previewImageForVideoWithFilepath:(NSURL *)filepath;

/**
 Returns a new filepath in the media folder with a given extension based on the current date/time
 
 @param extension The file type extension to use, e.g. "png"
 @return A filepath to a file in the media folder with the given extension
 */
- (NSURL *) libraryFilepathForCurrentTimestampWithExtension:(NSString *)extension;

/**
 Deletes an image or video file from the library.
 
 @param filepath The filepath of the file to delete
 
 @return YES if the file was found and deleted, otherwise NO.
 
 @see filepaths
 @see [FLIROneSDKStreamManager capturePhotoWithFilepath:]
 */
- (BOOL) deleteLibraryFileWithFilepath:(NSURL *)filepath;

/**
 Copies an image or video into the library.
 
 @param filepath The filepath of the file to copy into the library directory
 
 @param thumbnailFilepath The thumbnail filepath for the thumbnail of the image
 
 @return YES if the file was successfully copied, otherwise NO.
 
 @warning If a file with the same filename exists in the library folder, the copy operation will fail
 */
- (BOOL) copyImageToLibraryWithFilepath:(NSURL *)filepath withThumbnailFilepath:(NSURL *)thumbnailFilepath;

/**
 @param filepath The filepath of the file to check
 
 @return YES if the file with the specified name exists and is a video, otherwise NO.
 
 @see thumbnailForFilepath:
 */
- (BOOL)fileIsVideo:(NSURL *)filepath;
/**---------------------------------------------------------------------------------------
 * @name Properties
 *  ---------------------------------------------------------------------------------------
 */
/**
 An array of filepaths for all images and videos in the library.
 Each item is an NSURL representing the location of the image or video.
 
 @see thumbnailForFilepath:
 @see deleteLibraryFileWithFilepath:
 */
@property (readonly, nonatomic, strong) NSArray *filepaths;


/**
 The string representation of the folder on the device where the library media is stored.
 
 Any media saved to this folder should appear in the library UI. In order to add media to this folder,
 the FLIROneSDKImageEditor's finishEditingAndSaveCurrentImageToFilepath:withPreviewImage: method should be used.
 */
@property (readonly, nonatomic, strong) NSURL *mediaPath;

@end
