//
//  FLIROneSDKLibraryViewController.h
//  FLIROneSDK
//
//  Created by Joseph Colicchio on 4/22/14.
//  Copyright (c) 2014 FLIR. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 A ready made library view controller that allows a user to browse a list
 of captured images and videos, as well as preview, delete, and edit them.
 
 All functionality is implemented using the FLIROneSDKLibraryManager, FLIROneSDK, and FLIROneSDKShareActivity classes.
 
 You are not required to use this class, and may use your own FLIROneSDKDelegate(s) to
 display a library view to your users.
 
 @warning All interactions with this class must occur on the main thread.
 */
@interface FLIROneSDKLibraryViewController : UICollectionViewController <UICollectionViewDelegate, UICollectionViewDataSource, UIAlertViewDelegate>

/**
 Presents a library view controller modally.
 The view will be dismissed when the user taps the "back" button.
 
 @param viewController The parent view controller to use to present the FLIROneSDKLibraryManager
 */
+ (void) presentLibraryFromViewController:(UIViewController *)viewController;

/**
 The button used to present a FLIROneSDKShareActivity view controller.
 */
@property (nonatomic) UIBarButtonItem *shareButton;

/**
 The button used to delete one or more library items.
 */
@property (nonatomic) UIBarButtonItem *deleteButton;

/**
 The button used to navigate "backwards" within the pushed view controllers.
 */
@property (nonatomic) UIBarButtonItem *backButton;

/**
 The button used to switch to "multiple item selection" mode.
 */
@property (nonatomic) UIBarButtonItem *enableMultipleSelectionModeButton;

/**
 The button used to switch from "multiple item selection mode" back to "single item display" mode.
 */
@property (nonatomic) UIBarButtonItem *exitMultipleSelectionModeButton;

/**
 Toolbar at the bottom of the view that contains the share, delete, and cancel buttons.
 */
@property (nonatomic) UIToolbar *bottomBar;

/**
 The height of the bottomBar.
 */
@property (nonatomic) float toolbarHeight;

/**
 The view containing the "No Photos or Videos" information
 */
@property (nonatomic) UIView *libraryEmptyView;


@end
