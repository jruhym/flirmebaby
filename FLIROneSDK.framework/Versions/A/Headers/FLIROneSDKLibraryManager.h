//
//  FLIROneSDKLibraryManager.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 5/21/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 Provides NSURL filepath for a media folder and generates timestamped filepaths for saving new photos and videos to this folder
 
 @note You may choose to save images to any location in the file system
  
 @see [FLIROneSDKStreamManager startRecordingVideoWithFilepath:withVideoRendererDelegate:]
 @see [FLIROneSDKStreamManager capturePhotoWithFilepath:]
 @see [FLIROneSDKImageEditor loadImageWithFilepath:]
 */
@interface FLIROneSDKLibraryManager : NSObject

/**---------------------------------------------------------------------------------------
 * @name Media Methods
 *  ---------------------------------------------------------------------------------------
 */

/**The URL representation of the folder on the device where the library media can be stored

@return An NSURL representing the media folder
 
*/
+ (NSURL *)mediaPath;

/**Returns a new filepath in the media folder with a given extension based on the current date/time
 
 @param extension The file type extension to use, e.g. “png”
 
 @return A filepath to a file in the media folder with the given extension
 */
+ (NSURL *)libraryFilepathForCurrentTimestampWithExtension:(NSString *)extension;

@end
