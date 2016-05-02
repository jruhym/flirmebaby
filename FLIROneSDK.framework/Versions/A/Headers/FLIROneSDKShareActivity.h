//
//  FLIROneSDKShareActivity.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 4/30/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 A ready made UI that allows the user to share videos and photos with standard iOS sharing
 services, with the addition of the ability to upload directly to YouTube if the filenames
 array contains exactly one video file.
 
 All functionality is implemented using the FLIROneSDKLibraryManager class.
 
 You are not required to use this class, and may implement your own custom FLIROneSDKShareActivity.
 
 @warning All interactions with this class must occur on the main thread.
 */
@interface FLIROneSDKShareActivity : UIActivity

/**
 Presents the activity view controller modally for sharing the specified files from the library.
 
 @param filepaths An array of filepath NSURL instances that correspond to files in the FLIR ONE library
 @param viewController The view controller to present the FLIROneSDKShareActivity with
 */
+ (void) presentActivityViewControllerWithFilepaths:(NSArray *)filepaths withViewController:(UIViewController *)viewController;

/**
 Used to enable the YouTube upload interface on the share menu. Requires a valid Client ID and Client Key, available and configurable from the Google developers console.
 @param clientID The Client ID obtained through the Google developers console.
 @param clientKey The Client Key obtained through the Google developers console.
 */
+ (void) setClientID:(NSString *)clientID andClientKey:(NSString *)clientKey;

/**
 Used with Youtube upload interface. Returns the client ID, or nil if one has not been set.
 */
+ (NSString *) clientID;
/**
 Used with Youtube upload interface. Returns the client key, or nil if one has not been set.
 */
+ (NSString *) clientKey;

@end
