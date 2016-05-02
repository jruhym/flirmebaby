//
//  FLIROneSDKSimulation.h
//  FLIROneSDK
//
//  Created by Sean Burau on 6/12/15.
//  Copyright (c) 2015 flir. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Controls for a simulated FLIR ONE device.
 This class is intended to be used for debugging and testing purposes, and may
 be used on the iOS simulator or on a physical iOS device.
 
 @note If a physical FLIR ONE is connected while the simulated device is being used,
 the simulated FLIR ONE will be disconnected and disabled, and the physical FLIR ONE
 will when connect.
 */
@interface FLIROneSDKSimulation : NSObject

/**
 @return The singleton instance of the class.
 */
+(instancetype)sharedInstance;

/**
 Used to determine if the simulated FLIR ONE device can be used at the moment.
 Calling any of the methods in this class will have no effect while this method returns NO.
 
 @return YES if a physical device IS NOT connected, NO if a physical device IS connected.
 */
-(BOOL)isAvailable;

/**
 Connects a simulated FLIR ONE device using a bundle of frames.
 
 @param frameBundleName The name of the bundle to use as a source for frames, not including the .bundle extension.
 If this argument cannot be used to extract images from a properly formatted bundle, the default
 built-in frames will be used instead.
 
 @param batteryChargePercentage The initial battery charge percentage of the simulated device.
 Will be bounded to fit within the range of [1, 100], inclusive.
 
 @note This method will have no effect if the simulated device is already connected,
 or if the isAvailable method would return NO.
 */
-(void)connectWithFrameBundleName:(NSString *)frameBundleName withBatteryChargePercentage:(NSNumber *)batteryChargePercentage;

/**
 Disconnects the simulated FLIR ONE device.
 
 @note This method will have no effect if the simulated FLIR ONE device is not currently connected.
 */
-(void)disconnect;

/**
 Connects or disconnects the simulated charge cable to the simulated FLIR ONE.
 This property is initialized to YES.
 While set to YES, the battery level of the simulated device will increase over time.
 While set to NO, the battery level of the  simulated device will decrease over time.
 
 @warning Like a physical device, if the battery level of the simulated FLIR ONE is allowed to reach empty,
 the device will disconnect.
 
 @param newChargeCableConnectionState YES if the charge cable should be connected, NO if it should be disconnected.
 */
-(void)setChargeCableState:(BOOL)newChargeCableConnectionState;

@end
