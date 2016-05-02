//
//  FLIROneSDKUIImage.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 9/15/14.
//  Copyright (c) 2014 flir. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <FLIROneSDK/FLIROneSDKTypes.h>

/**
 FLIROneSDKUIImage is a UIImage class which allows initialization using data returned by the FLIROneSDKStreamManagerDelegate or FLIROneSDKImageEditorDelegate callbacks
 
 @see FLIROneSDKStreamManagerDelegate
 @see FLIROneSDKImageEditorDelegate
 */

@interface FLIROneSDKUIImage : UIImage

/**
 The original data used to generate this UIImage
 */
@property (strong, nonatomic, readonly) NSData *data;

/**
 Create an image from formatted data, using size if necessary
 
 @param format The image format corresponding to the data
 @param data The image data used to create the image
 @param size The size of the image. For JPEG format, this size is ignored, CGSizeZero is suggested
 @return the FLIROneSDKUIImage, or nil if it could not be created
 */
+ (instancetype) imageWithFormat:(FLIROneSDKImageOptions)format andData:(NSData *)data andSize:(CGSize)size;

/**
 Initialize an image from formatted data, using size if necessary
 
 @param format The image format corresponding to the data
 @param data The image data used to create the image
 @param size The size of the image, if necessary
 */
- (instancetype) initWithFormat:(FLIROneSDKImageOptions)format andData:(NSData *)data andSize:(CGSize)size;

@end
