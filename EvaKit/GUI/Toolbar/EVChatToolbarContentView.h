//
//  EVChatToolbarView.h
//  EvaKit
//
//  Created by Yegor Popovych on 7/9/15.
//  Copyright (c) 2015 Evature. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <JSQMessagesViewController/JSQMessages.h>

@class EVChatToolbarContentView;

@protocol EVChatToolbarContentViewTouchDelegate <NSObject>

- (void)leftButtonTouched:(EVChatToolbarContentView*)toolbarContentView;
- (void)centerButtonTouched:(EVChatToolbarContentView*)toolbarContentView;
- (void)rightButtonTouched:(EVChatToolbarContentView*)toolbarContentView;

@end

@interface EVChatToolbarContentView : JSQMessagesToolbarContentView

@property (nonatomic, assign) id<EVChatToolbarContentViewTouchDelegate> touchDelegate;

@property (nonatomic, strong) UIColor *centerButtonMicLineColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat centerButtonMicLineWidth UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIColor *centerButtonMicColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat centerButtonMicScale UI_APPEARANCE_SELECTOR;

@property (nonatomic, strong) UIColor *centerButtonBackgroundColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIColor *centerButtonBorderColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIColor *centerButtonHighlightColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat centerButtonBorderWidth UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat centerButtonSpinningBorderWidth UI_APPEARANCE_SELECTOR;


@property (nonatomic, strong) UIColor *leftRightButtonsBackgroundColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIColor *leftRightButtonsImageColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, strong) UIColor *leftRightButtonsBorderColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat leftRightButtonsBorderWidth UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat leftRightButtonsImageScale UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat leftRightButtonsUnactiveBackgroundScale UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat leftRightButtonsActiveBackgroundScale UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat leftRightButtonsMaxImageScale UI_APPEARANCE_SELECTOR;
@property (nonatomic, assign) CGFloat leftRightButtonsMaxBackgroundScale UI_APPEARANCE_SELECTOR;


@property (nonatomic, assign) CGFloat leftRightButtonsOffset UI_APPEARANCE_SELECTOR;

- (void)audioSessionStarted;
- (void)audioSessionStoped;

- (void)startWaitAnimation;
- (void)stopWaitAnimation;

- (void)newAudioLevelData:(NSData*)data;
- (void)newMinVolume:(CGFloat)minVolume andMaxVolume:(CGFloat)maxVolume;

@end