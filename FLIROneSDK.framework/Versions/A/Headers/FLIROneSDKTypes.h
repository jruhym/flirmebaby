//
//  FLIROneSDKTypes.h
//  FLIROneSDK
//
//  Created by Sean Burau on 5/21/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#ifndef FLIROneSDK_FLIROneSDKTypes_h
#define FLIROneSDK_FLIROneSDKTypes_h

#import <FLIROneSDK/FLIROneSDKPalette.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 The result of attempting to capture an image or video.
 */
typedef NS_ENUM(NSUInteger, FLIROneSDKCaptureStatus) {
    /**
     The capture was successful.
     */
    FLIROneSDKCaptureStatusSucceeded,
    
    /**
     The capture failed for an unknown reason.
     */
    FLIROneSDKCaptureStatusFailedWithUnknownError,
};

/**
 Enumerates all possible states of the thermal camera's battery charging status.
 */
typedef NS_ENUM(NSInteger, FLIROneSDKBatteryChargingState) {
    /**
     The FLIR ONE battery is discharging.
     */
    FLIROneSDKBatteryChargingStateDischarging,
    
    /**
     The FLIR ONE battery is charging from external power.
     */
    FLIROneSDKBatteryChargingStateCharging,
    
    /**
     The FLIR ONE battery's charging state cannot be read due to a fault or some other error.
     */
    FLIROneSDKBatteryChargingStateError,
    
    /**
     An invalid charging state. You should not receive this.
     */
    FLIROneSDKBatteryChargingStateInvalid,
};

/**
 The state of the "tuning" status of the FLIR ONE device. The tuning status is updated when the device determines that its temperature points are becoming inaccurate or, in the case of a gen 1 sled, if the user initiates tuning by pulling down on the shutter handle
 
 @note It is important to update the user with the progress of tuning. Keep in mind all UI updates should be performed on the main thread.
 
 @see [FLIROneSDKStreamManagerDelegate FLIROneSDKTuningStateDidChange:]
 */
typedef NS_ENUM(NSUInteger, FLIROneSDKTuningState) {
    /**
     The FLIR ONE requires tuning. When in this state, tuning is required for frames to have radiometric temperature data. If you application requires temperature data you must force the user to tune their device.
     */
    FLIROneSDKTuningStateTuningRequired,
    
    /**
     The FLIR ONE is in the process of being tuned, but has not yet finished. The tuning UI should be updated asking the user to continue holding down on the shutter handle
     */
    FLIROneSDKTuningStateInProgress,
    
    /**
     The FLIR ONE has been tuned and the user should release the shutter handle.
     */
    FLIROneSDKTuningStateTunedWithClosedShutter,
    
    /**
     The shutter has been released to the "open" position and the tuning interface should be dismissed.
     */
    FLIROneSDKTuningStateTunedWithOpenedShutter,
    
    /**
     The camera is requesting, but not requiring, that the shutter be pulled into the "closed down" position
     in order to re-tune the FLIR ONE. If you application requires high quality temperature data you must force the user to tune their device. Otherwise you may ignore this tuning state.
     */
    FLIROneSDKTuningStateTuningSuggested,
    
    /**
     The camera has recently started, and the temperature values measured may be slightly inaccurate.
     */
    FLIROneSDKTuningStateApproximatelyTunedWithOpenedShutter,
    
    /**
     An invalid tuning state. You should not receive this state from the FLIR ONE device.
     */
    FLIROneSDKTuningStateUnknown,
};

/**
 The result of attempting an IO operation with a FLIROneSDKImage.
 */
typedef NS_ENUM(NSUInteger, FLIROneSDKImageIOStatus){
    /**
     The IO operation failed for an unknown reason.
     */
    FLIROneSDKImageIOStatusFailedWithUnknownError,
    
    /**
     The image editor has not loaded a file to save.
     */
    FLIROneSDKImageIOStatusFailedWithNoImageLoaded,
    
    /**
     The supplied URL was missing or invalid.
     */
    FLIROneSDKImageIOStatusFailedWithInvalidURL,
    
    /**
     The file could not be found at given URL.
     */
    FLIROneSDKImageIOStatusFailedWithFileNotFound,
    
    /**
     The file was of an unsupported file type.
     */
    FLIROneSDKImageIOStatusFailedWithFileFormatNotSupported,
    
    /**
     The IO operation completed successfully.
     */
    FLIROneSDKImageIOStatusSucceeded,
};

/**
 Image options allow user to specify what data is used/returned when streaming frames or loading images from disk
 Can be OR'd together to create a mask of options regarding image generation
 */
typedef NS_ENUM(uint64_t, FLIROneSDKImageOptions) {
    /**
     Linear 14 bit image data
     */
    FLIROneSDKImageOptionsThermalLinearFlux14BitImage = 0x1,
    /**
     Thermal RGBA image data
     */
    FLIROneSDKImageOptionsThermalRGBA8888Image = 0x2,
    /**
     MSX (thermal + visual) RGBA image data
     */
    FLIROneSDKImageOptionsBlendedMSXRGBA8888Image = 0x4,
    /**
     Visual JPEG image data
     */
    FLIROneSDKImageOptionsVisualJPEGImage = 0x8,
    /**
     Visual YCbCr image data
     */
    FLIROneSDKImageOptionsVisualYCbCr888Image = 0x10,
    /**
     Radiometric kelvin temperature data
     
     @note The data is in units of kelvin * 100, so 273.15ºK is represented as 27,315
     */
    FLIROneSDKImageOptionsThermalRadiometricKelvinImage = 0x20,
    /**
     Radiometric kelvin temperature data
     
     @note The data is float representation of Kelvin temperatures
     */
    FLIROneSDKImageOptionsThermalRadiometricKelvinImageFloat = 0x40,
};

typedef struct {
    uint8_t Y;
    uint8_t Cb;
    uint8_t Cr;
} FLIROneSDKYCbCr888Pixel;

typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
} FLIROneSDKRGBA8888Pixel;

extern const CGFloat FLIROneSDKEmissivityMatte;
extern const CGFloat FLIROneSDKEmissivitySemiMatte;
extern const CGFloat FLIROneSDKEmissivitySemiGlossy;
extern const CGFloat FLIROneSDKEmissivityGlossy;

/**
 Vivid IR Quality allows user to optionally change the quality of FLIR One Pro (Gen 3) streamed images. This value defaults to High but can be set to Low or None to lower quality and improve framerate.
 
 @note Vivid IR is not available on FLIR One Consumer (Gen 3) and Gen 2 devices, so this value is always None for these devices
 */
typedef NS_ENUM(uint64_t, FLIROneSDKVividIRQuality) {
    /**
     No Vivid IR
     */
    FLIROneSDKVividIRQualityNone,
    /**
     Low Quality Vivid IR
     */
    FLIROneSDKVividIRQualityLow,
    /**
     High Quality Vivid IR
     */
    FLIROneSDKVividIRQualityHigh,
};

#endif
