//
//  FLIROneSDKLibraryDetailViewController.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 4/23/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FLIROneSDKLibraryDetailViewController : UICollectionViewController <UICollectionViewDataSource, UICollectionViewDelegate, UICollectionViewDelegateFlowLayout>

- (instancetype) initWithFilepath:(NSURL *)filepath;
- (instancetype) initWithIndex:(NSUInteger)index;

@property (strong, nonatomic) UIToolbar *bottomBar;
@property (strong, nonatomic) UIBarButtonItem *editButton;
@property (strong, nonatomic) UIBarButtonItem *deleteButton;
@property (strong, nonatomic) UIBarButtonItem *shareButton;
@property (strong, nonatomic) UIBarButtonItem *doneButton;

- (void) editCurrentItem;

- (void) deleteCurrentItem;

- (void) shareCurrentItem;

- (void) updateButtonsForFilepath:(NSURL *)filepath;

@end
