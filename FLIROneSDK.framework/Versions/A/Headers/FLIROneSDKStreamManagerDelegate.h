//
//  FLIROneSDKStreamManagerDelegate.h
//  FLIROneSDK
//
//  Created by Sean Burau on 9/16/14.
//  Copyright (c) 2014 flir. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FLIROneSDK/FLIROneSDKImageReceiverDelegate.h>

/**
 The stream delegate provides users with the ability to detect connection events, tuning information, and battery status, as well as capture videos and thermal images to disk
 */

@protocol FLIROneSDKStreamManagerDelegate <FLIROneSDKImageReceiverDelegate, NSObject>

@optional

/**---------------------------------------------------------------------------------------
 * @name Responding to Connection and Disconnection from the FLIR ONE device
 *  ---------------------------------------------------------------------------------------
 */
/**
 Triggered just after the FLIR ONE device has established communication. This is the first event received when a device connects. You MUST be connected to the FLIR ONE device in order to receive frames or any information from the sled. If your application is not receiving this event insure that the project dependencies are set up correctly and that the sled is working.
 
 When this event is triggered the app should track that the state of the app has been connected and update the UI. Before this event is triggered the UI should ask the user to connect their device.
 
 @warning It is important to always update the UI on the main thread.
 */
- (void) FLIROneSDKDidConnect;

/**
 Triggered just after FLIR ONE device has lost communication. This will only fire if connectivity was previously established.
 
 When this event is triggered the app should track that the state of the app has been disconnected and update the UI asking the user to connect their device.
 
 @warning It is important to always update the UI on the main thread.
 */
- (void) FLIROneSDKDidDisconnect;


/**---------------------------------------------------------------------------------------
 * @name Responding to Changes in the Battery or Charging State
 *  ---------------------------------------------------------------------------------------
 */
/**
 Triggered when the FLIR ONE's battery charging state changes.
 
 @param state The new charging state of the battery.
 
 @see FLIROneSDKBatteryChargingState
 @see FLIROneSDKBatteryPercentageDidChange:
 @warning It is important to always update the UI on the main thread.
 @deprecated This method is currently not yet implemented and will never be called
 */
- (void) FLIROneSDKBatteryChargingStateDidChange:(FLIROneSDKBatteryChargingState) state;

/**
 Triggered when the FLIR ONE's battery charge percentage changes.
 
 @param percentage The new charge percentage of the battery as an integer between 0 and 100, inclusive.
 
 @see FLIROneSDKBatteryChargingStateDidChange:
 @warning It is important to always update the UI on the main thread.
 @deprecated This method is currently not yet implemented and will never be called
 */
- (void) FLIROneSDKBatteryPercentageDidChange:(NSNumber *) percentage;

/**---------------------------------------------------------------------------------------
 * @name Responding to Changes in the Tuning State
 *  ---------------------------------------------------------------------------------------
 */
/**
 Triggered when the "tuning state" of the FLIR ONE changes. It is important
 
 @param newTuningState The new tuning state of the FLIR ONE.
 
 @see FLIROneSDKTuningState
 @warning It is important to always update the UI on the main thread.
 */
- (void) FLIROneSDKTuningStateDidChange:(FLIROneSDKTuningState)newTuningState;


/**
 Triggered when the automatic tuning feature is enabled or disabled, for 
 devices with automatic tuning shutters.
 @param deviceWillTuneAutomatically Will be 0 if automatic tuning is turned off
 */
- (void) FLIROneSDKAutomaticTuningDidChange:(NSNumber *)deviceWillTuneAutomatically;

/**---------------------------------------------------------------------------------------
 * @name Responding to FLIROneSDKStreamManager, Capturing Photos or Videos
 *  ---------------------------------------------------------------------------------------
 */
/**
 Triggered when a photo capture request is sent to the FLIROneSDKStreamManager singleton instance.
 This event will always fire, even in the capture fails.
 
 @param captureStatus The result of the photo capture. Indicates whether or not the capture completed successfully.
 @param filepath If the capture was successful, will be a NSURL representing the location of the captured photo, otherwise
 nil. Use this string with the FLIROneSDKLibraryManager singleton instance to retrieve a thumbnail and the absolute file path of the video.
 
 @see [FLIROneSDKStreamManager capturePhotoWithFilepath:]
 @see FLIROneSDKLibraryManager
 @see FLIROneSDKCaptureStatus
 */
- (void) FLIROneSDKDidFinishCapturingPhoto:(FLIROneSDKCaptureStatus)captureStatus withFilepath:(NSURL *)filepath;

/**
 Triggered after a FLIROneSDKStreamManager startRecordingVideo request.
 This event will always fire, even if the video capture could not be started.
 
 @param captureStartStatus The result of attempting to start capturing video. Indicates whether or not capture started successfully.
 
 @see [FLIROneSDKStreamManager startRecordingVideoWithFilepath:withVideoRendererDelegate:]
 @see FLIROneSDKCaptureStatus
 
 */
- (void) FLIROneSDKDidStartRecordingVideo:(FLIROneSDKCaptureStatus)captureStartStatus;

/**
 Triggered after a FLIROneSDKStreamManager stopRecordingVideo request, or if a recording is halted prematurely due to an error.
 This event will always trigger after calling stopRecordingVideo, even if the video capture has not been started.
 
 @param captureStopStatus The reason why capture was stopped, or an error indicating that capture was not active.
 
 @warning If FLIROneSDKDidStartRecordingVideo was triggered with an error result, this method will not be triggered.
 
 @see [FLIROneSDKStreamManager stopRecordingVideo]
 @see FLIROneSDKCaptureStatus
 
 */
- (void) FLIROneSDKDidStopRecordingVideo:(FLIROneSDKCaptureStatus)captureStopStatus;

/**
 Triggered after a captured video has been written to disk.
 This event will only fire if FLIROneSDKDidStopRecordingVideo was triggered and video capture was active previously.
 
 
 @param captureWriteStatus The result of attempting to write the video to disk.
 @param filepath If the file was successfully written to disk, will be a NSURL representing the location of the saved video, otherwise nil.
 Use this string with the FLIROneSDKLibraryManager singleton instance to retrieve a thumbnail and the absolute file path of the video.
 
 @warning If FLIROneSDKDidStartRecordingVideo was triggered with an error result, this method will not be triggered.
 
 @see [FLIROneSDKStreamManagerDelegate FLIROneSDKDidStopRecordingVideo:]
 @see FLIROneSDKLibraryManager
 @see FLIROneSDKCaptureStatus
 */

- (void) FLIROneSDKDidFinishWritingVideo:(FLIROneSDKCaptureStatus)captureWriteStatus withFilepath:(NSURL *)filepath;

@end
