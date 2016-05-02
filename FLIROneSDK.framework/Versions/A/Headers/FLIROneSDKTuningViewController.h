//
//  FLIROneSDKTuningViewController.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 4/10/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 A ready made view controller that can be used to instruct the user to pull the shutter
 to tune the FLIR ONE.
 
 You are not required to use this class, and may use your own FLIROneSDKDelegate(s) to
 update your UI to guide the user through the tuning process.
 
 To successfully using this tuning view controller you will need to achieve the following points:
 
    - You will still need to implement your own logic for handling connection and disconnection from the FLIR ONE device. This tuning view does not prompt the user to connect the sled, and will dismiss itself if the device disconnects.
 
    - You will still need to implement your own logic for how to respond to tuning events from the method [FLIROneSDKDelegate FLIROneSDKTuningStateDidChange:]
 
    - You will need to track if this tuning view controller has already been presented. If you attempt to present the FLIROneSDKTuningViewController when it is already presented it will return NO to indicate that an error has occurred.
 
 When the tuning view controller is presented it become the active view controller, and it will sign up as a FLIROneSDKDelegate that subscribes to tuning events that occur in the method [FLIROneSDKDelegate FLIROneSDKTuningStateDidChange:]. It will handle these events and dismiss itself when the tuning process is completed.
 
 For custom applications, you will likely want to implement you own tuning UI to have the desired look and feel for your application.
 
 @warning All interactions with this class must occur on the main thread.
 */
@interface FLIROneSDKTuningViewController : UIViewController <FLIROneSDKStreamManagerDelegate, FLIROneSDKImageReceiverDelegate>

/**
 Presents a view controller modally that will guide the user through the tuning process.
 
 This view controller will register itself as a FLIROneSDKDelegate and will automatically dismiss
 itself when the tuning state is changed to FLIROneSDKTuningStateTunedWithOpenedShutter, or the FLIR
 One disconnects.
 
 @param viewController The parent view controller to use to present the FLIROneSDKTuningViewController
 @param tuningState The tuning state to display initially
 
 @return Boolean value representing the success or failure of the presentation action. YES means the view controller was successfully presented.
 
 @warning You should call this method from within the FLIROneSDKTuningStateDidChange callback, when the tuning state changes to FLIROneSDKTuningStateTuningRequired, FLIROneSDKTuningStateInProgress, or FLIROneSDKTuningStateTunedWithClosedShutter.
 @warning You should not call this method unless the sled is connected to the device.
 */
+ (BOOL) presentWithViewController:(UIViewController *)viewController withTuningState:(FLIROneSDKTuningState)tuningState;

@end
