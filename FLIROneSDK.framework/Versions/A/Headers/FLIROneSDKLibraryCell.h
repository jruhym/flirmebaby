//
//  FLIROneSDKLibraryCell.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 4/22/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FLIROneSDKLibraryCell : UICollectionViewCell

/**
 updateUI is called whenever the cell is selected or deselected, or when the filename is set
 */
- (void) updateUI;

/**
 Setting the filename will cause the cell to load the file's thumbnail and update itself
 */
- (void) setFilepath:(NSURL *)filepath;

/**
 Set the filename
 */

@property (strong, nonatomic, readonly) NSURL *filepath;

@property (strong, nonatomic) UIImageView *playButtonView;

@property (strong, nonatomic) UIImageView *checkboxView;

@property (strong, nonatomic) UIImageView *imageView;

@end
