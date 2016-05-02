//
//  FLIROneSDK.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 4/4/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <FLIROneSDK/FLIROneSDKImageReceiverDelegate.h>
#import <FLIROneSDK/FLIROneSDKDelegateManager.h>

#import <FLIROneSDK/FLIROneSDKStreamManagerDelegate.h>
#import <FLIROneSDK/FLIROneSDKImageEditorDelegate.h>
#import <FLIROneSDK/FLIROneSDKImageReceiverDelegate.h>
#import <FLIROneSDK/FLIROneSDKVideoRendererDelegate.h>

#import <FLIROneSDK/FLIROneSDKImagePropertyController.h>

#import <FLIROneSDK/FLIROneSDKStreamManager.h>
#import <FLIROneSDK/FLIROneSDKImageEditor.h>
#import <FLIROneSDK/FLIROneSDKPalette.h>
#import <FLIROneSDK/FLIROneSDKLibraryManager.h>
#import <FLIROneSDK/FLIROneSDKTypes.h>

#import <FLIROneSDK/FLIROneSDKTuningViewController.h>
#import <FLIROneSDK/FLIROneSDKLibraryViewController.h>
#import <FLIROneSDK/FLIROneSDKShareActivity.h>

#import <FLIROneSDK/FLIROneSDKImageMetadata.h>
#import <FLIROneSDK/FLIROneSDKUIImage.h>

/** 
 This class informs the developer of the SDK's version, and maintains user settings for the pre-built UI. Currently, the only setting implemented is temperature unit (C or F).
 */
@interface FLIROneSDK : NSObject

/**---------------------------------------------------------------------------------------
 * @name Accessing the SDK sharedInstance
 *  ---------------------------------------------------------------------------------------
 */
/**Accesses and returns a reference to the global singleton instance. If a singleton has not been initialized yet, it will initialize the singleton instance.
 
 The FLIROneSDK is exclusively accessed via a reference to the singleton instance. All of the instance methods will be called on this singleton object. This FLIROneSDK singleton object keeps track of the objects registered as FLIROneSDK delegates. This object is responsible for adding and removing delegates. Registering a FLIROneSDKDelegate is required to receive any and all information from the FLIR ONE device including connection state and receiving frames. See FLIROneSDKDelegate.
 
 @return A reference to the global singleton instance.
 @see FLIROneSDKStreamManagerDelegate
 */
+ (instancetype)sharedInstance;

/**---------------------------------------------------------------------------------------
 * @name Accessing the SDK Version
 *  ---------------------------------------------------------------------------------------
 */
/**
 The current version of the SDK, this will only change if you use a different version of the SDK entirely
 */
- (NSString *) version;

/**
 Whether or not the default UI elements display temperatures in Celsius, or alternatively in Fahrenheit
 The default value is based on the phone's location
 */
@property (nonatomic) BOOL userInterfaceUsesCelsius;

@end
