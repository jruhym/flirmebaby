//
//  FLIROneSDKStreamManager.h
//  FLIROneSDK
//
//  Created by Sean Burau on 5/21/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>

#import <FLIROneSDK/FLIROneSDKImagePropertyController.h>
#import <FLIROneSDK/FLIROneSDKStreamManagerDelegate.h>
#import <FLIROneSDK/FLIROneSDKImageReceiverDelegate.h>
#import <FLIROneSDK/FLIROneSDKDelegateManager.h>
#import <FLIROneSDK/FLIROneSDKVideoRendererDelegate.h>

/**
 Used for controlling data capture from a live image stream.
 FLIROneSDKDelegate callbacks will be triggered in response to the methods
 used in this class. 
 
 The sharedInstance of this class is responsible for setting the properties of incoming frames such as the current color palette or emissivity, and for capturing images or videos.
 
 All instance methods must be called on the singleton instance returned by the FLIROneSDKStreamManager sharedInstance: method.
 
 @note This class is thread safe; you may call any method from any thread
 without issue.
 
 @warning Do not attempt to create another instance of this class. Always
 use the sharedInstance class method to retrieve the global singleton.
 */
@interface FLIROneSDKStreamManager : NSObject <FLIROneSDKImagePropertyController>

/**---------------------------------------------------------------------------------------
 * @name Accessing the FLIROneSDKStreamManager sharedInstance
 *  ---------------------------------------------------------------------------------------
 */
/**Accesses and returns a reference to the global singleton instance. If a singleton has not been initialized yet, it will initialize the singleton instance.
 
 The FLIROneSDKStreamManager is exclusively accessed via a reference to the singleton instance. All of the instance methods will be called on this singleton object. This FLIROneSDK singleton object keeps track of the objects registered as FLIROneSDK delegates. This object is responsible for adding and removing delegates. Registering a FLIROneSDKDelegate is required to receive any and all information from the FLIR ONE device including connection state and receiving frames. See FLIROneSDKDelegate.
 
 @return A reference to the global singleton instance.
 @see FLIROneSDKStreamManagerDelegate
 @warning The Stream Manager sharedInstance should only be accessed after a FLIROneSDKDelegate has been added
 */
+ (instancetype) sharedInstance;

/**Register a new delegate for FLIR ONE events. If the delegate has already been added previously, this method will have no effect.
 
 As an example to register the current view controller as a FLIROneSDKDelegate:
 
 [[FLIROneSDK sharedInstance] addDelegate:self];
 
 @param delegate The object to register for FLIR ONE callback events.
 */
- (void) addDelegate:(id <FLIROneSDKStreamManagerDelegate, FLIROneSDKImageReceiverDelegate>) delegate;

/**
 Unsubscribe an object that was previously registered with addDelegate from receiving FLIR ONE events.
 If the delegate was not been previously added, this method will have no effect.
 
 @param delegate The object to unsubscribe from FLIR ONE callback events
 */
- (void) removeDelegate:(id <FLIROneSDKStreamManagerDelegate, FLIROneSDKImageReceiverDelegate>) delegate;

/**---------------------------------------------------------------------------------------
 * @name Capturing a Photo or Video
 *  ---------------------------------------------------------------------------------------
 */
/**
 Begins recording video. Every call to this method will result in the 
 FLIROneSDKDidStartRecordingVideo callback being triggered for all registered
 delegates.
 
 @param filepath The filepath where the video should be saved
 @note If the filepath is a file in the FLIROneSDKLibraryManager's media folder, the video will be added to the library and will be visible in the library's UI
 
 @param videoRendererDelegate An optional video recorder delegate for recording in the image format of your choice, or for making modifications to each frame
 
 @note Calling this method while recording has already started will not affect
 the current recording, but will still result in the delegate callback firing.
 
 @note This method will save a thumbnail to the given location by appending ".thumb" to the filepath
 @note This method will save a full-size preview of the video to the given location by appending ".preview" to the filepath
 
 @see [FLIROneSDKStreamManagerDelegate FLIROneSDKDidStartRecordingVideo:]
 @see [FLIROneSDKLibraryManager mediaPath]
 @see [FLIROneSDKLibraryManager libraryFilepathForCurrentTimestampWithExtension:]
 
 */

- (void) startRecordingVideoWithFilepath:(NSURL *)filepath withVideoRendererDelegate:(id<FLIROneSDKVideoRendererDelegate>)videoRendererDelegate;

/**
 Ends an ongoing video recording. Every call to this method will result in the
 FLIROneSDKDidStopRecording callback being triggered for all registered delegates.
 If the there was an ongoing recording at the time, you should also expect a
 FLIROneSDKDidFinishWritingVideo callback to be triggered afterwords.
 
 @note Calling this method after recording has already stopped will not affect
 the current recording, but will still result in the delegate callback firing.
 
 @see startRecordingVideoWithFilepath:withVideoRendererDelegate:
 @see [FLIROneSDKStreamManagerDelegate FLIROneSDKDidStopRecordingVideo:]
 @see FLIROneSDK
 
 */
- (void) stopRecordingVideo;

/**
 Instructs the SDK to save the current frame to the media library folder on disk.
 Every call to this method will result in the FLIROneSDKDidFinishCapturingPhoto
 callback being triggered for all registered delegates.
 
 @param filepath The filepath where the captured image should be saved
 
 @note If the filepath is a file in the FLIROneSDKLibraryManager's media folder, the image will be added to the library and will show up in the Library UI elements
 
 @warning You must wait for the FLIROneSDKDidFinishCapturingPhoto:withFilepath: callback to fire
 before calling this method again, or the request will fail immediately.
 
 @warning Do not attempt to capture photos while the sled is in a tuning state. Wait until tuning has completed before capturing media to the library
 
 @note This method will save a thumbnail to the given location by appending ".thumb" to the filepath
 
 @see [FLIROneSDKStreamManagerDelegate FLIROneSDKDidFinishCapturingPhoto:withFilepath:]
 @see [FLIROneSDKImageEditor loadImageWithFilepath:]
 @see [FLIROneSDKLibraryManager mediaPath]
 @see [FLIROneSDKLibraryManager libraryFilepathForCurrentTimestampWithExtension:]
 */
- (void) capturePhotoWithFilepath:(NSURL *)filepath;

/**
 If the camera has an automatic tuning shutter, commands the camera to tune the thermal image using the automatic shutter.
 */
- (void) performTuning;

/**
 For cameras with automatic tuning shutter, the camera will automatically tune when
 needed by default. If tuning should be disabled, call this method with false.
 @param shouldTuneAutomatically The desired state of automatic tuning.
 */
- (void) setAutomaticTuning:(BOOL)shouldTuneAutomatically;

/**
 Determine whether the device connected is a dongle or sled
 */
- (BOOL) isDongle;

/**
 Flag indicating whether or not MSX distance is enabled.
 MSX distance controls the alignment of the visual and thermal elements of a MSX image.
 */
@property (readwrite, nonatomic) BOOL msxDistanceEnabled;

/**
 CGFloat between 0-1 specifying MSX distance, 0 being closest and 1 being farthest.
 */
@property (readwrite, nonatomic) CGFloat msxDistance;



@end
