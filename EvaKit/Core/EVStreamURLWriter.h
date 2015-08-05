//
//  EVStreamURLWriter.h
//  EvaKit
//
//  Created by Yegor Popovych on 8/5/15.
//  Copyright (c) 2015 Evature. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EVDataProvider.h"

//Provider delegate methods in this class stops caller run lopp. So Use only in background loops
@protocol EVStreamURLWriterDelegate;

@interface EVStreamURLWriter : NSObject <EVDataProviderDelegate>

- (instancetype)initWithURL:(NSURL*)anURL
                    headers:(NSDictionary*)headers
                 bufferSize:(NSUInteger)bufferSize
                   delegate:(id<EVStreamURLWriterDelegate>)delegate
                    inQueue:(dispatch_queue_t)queue
                  debugMode:(BOOL)isDebug;

@property (nonatomic, assign, readwrite) id<EVStreamURLWriterDelegate> delegate;

@property (nonatomic, assign, readwrite) BOOL isDebugMode;

@end


@protocol EVStreamURLWriterDelegate <NSObject>

- (void)streamWriter:(EVStreamURLWriter*)writer gotResponseData:(NSData*)data;
- (void)streamWriter:(EVStreamURLWriter *)writer gotAnError:(NSError*)error;
- (void)streamWriterFinished:(EVStreamURLWriter *)writer;

@end