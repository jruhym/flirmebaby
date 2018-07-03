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

#import <FLIROneSDK/FLIROneSDKImageMetadata.h>
#import <FLIROneSDK/FLIROneSDKUIImage.h>

/** 
 This class informs the developer of the SDK's version
 */
@interface FLIROneSDK : NSObject

/**---------------------------------------------------------------------------------------
 * @name Accessing the SDK Version
 *  ---------------------------------------------------------------------------------------
 */
/**
 The current version of the SDK, this will only change if you use a different version of the SDK entirely
 */
+ (NSString *) version;

@end
