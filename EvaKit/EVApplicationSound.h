//
//  EVApplicationSound.h
//  EvaKit
//
//  Created by Yegor Popovych on 8/21/15.
//  Copyright (c) 2015 Evature. All rights reserved.
//

#import <Foundation/Foundation.h>

// Supports only CAF, AIF, or WAV files. And length less than 30 seconds.
@interface EVApplicationSound : NSObject

@property (nonatomic, strong, readonly) NSString* filePath;

+ (instancetype)soundWithPath:(NSString*)path;
- (instancetype)initWithPath:(NSString*)path;

- (void)play;

@end
