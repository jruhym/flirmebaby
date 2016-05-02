//
//  FLIROneSDKPalette.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 5/20/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Used to specify the color scheme used for rendering the thermal component of MSX images, or thermal images.
 
 This class is used to get the list of palettes available from the SDK. Palettes accessed from this class are used to set the current palette for the FLIROneSDKStreamManager before image capture or to edit the palette of an image using the [FLIROneSDKImageEditor setPalette:] method after collection. For example:
    
    //set the current palette to the first palette in the list of palettes
    [FLIROneSDKStreamManager sharedInstance].palette = [[FLIROneSDKPalette palettes] firstObject];
 
 @warning Do not attempt to instantiate new instances of this class. You should instead select
 an instance using the palettes property
 */
@interface FLIROneSDKPalette : NSObject

/**---------------------------------------------------------------------------------------
 * @name Accessing Palette Objects
 *  ---------------------------------------------------------------------------------------
 */

/**
 An dictionary mapping string names to corresponding palettes.
 */
+(NSDictionary *)palettes;

/**---------------------------------------------------------------------------------------
 * @name Palette Properties
 *  ---------------------------------------------------------------------------------------
 */
/**
 Doubles as the display name and unique identifier for the palette.
 You can use this value to retrieve a specific palette instance via
 the palettes class method.
 @see palettes
 */
@property (readonly, strong, nonatomic) NSString *name;

@end
