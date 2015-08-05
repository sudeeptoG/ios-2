//
//  EVAudioDataStreamer.m
//  EvaKit
//
//  Created by Yegor Popovych on 8/5/15.
//  Copyright (c) 2015 Evature. All rights reserved.
//

#import "EVAudioDataStreamer.h"
#import "EVStreamURLWriter.h"



@interface EVAudioDataStreamer () <EVStreamURLWriterDelegate>

@property (nonatomic, strong, readwrite) NSMutableData* responseData;

@end

@implementation EVAudioDataStreamer

- (instancetype)initWithOperationChainLength:(NSUInteger)length {
    self = [super initWithOperationChainLength:length];
    if (self != nil) {
        self.responseData = [NSMutableData data];
        self.httpBufferSize = 0;
    }
    return self;
}

-  (void)dealloc {
    [self.dataProviderDelegate release];
    self.dataProviderDelegate = nil;
    self.responseData = nil;
    [super dealloc];
}

- (void)setHttpBufferSize:(NSUInteger)httpBufferSize {
    httpBufferSize = httpBufferSize > 32768 ? httpBufferSize : 32768;
    _httpBufferSize = httpBufferSize;
}

- (void)providerStarted:(id<EVDataProvider>)provider {
    [self.responseData setLength:0];
    EVStreamURLWriter* streamWriter = [[EVStreamURLWriter alloc] initWithURL:self.webServiceURL
                                                                     headers:@{
                                                                               @"Expect": @"100-continue",
                                                                               @"Transfer-Encoding": @"chunked",
                                                                               @"Content-Type": [NSString stringWithFormat:@"audio/x-flac;rate=%u", self.sampleRate]
                                                                               }
                                                                  bufferSize:self.httpBufferSize
                                                                    delegate:self
                                                                     inQueue:dispatch_get_main_queue()
                                                                   debugMode:self.isDebugMode];
    self.dataProviderDelegate = streamWriter;
    if (streamWriter == nil) {
        [self provider:self gotAnError:[NSError errorWithCode:EVAudioDataStreamerCreateErrorCode andDescription:@"Can't create stream writer"]];
    } else {
        [super providerStarted:provider];
    }
}

- (void)provider:(id<EVDataProvider>)provider gotAnError:(NSError *)error {
    [super provider:provider gotAnError:error];
    [self.delegate audioDataStreamerFailed:self withError:error];
}

- (NSData*)processData:(NSData*)data error:(NSError**)error {
    return data;
}


- (void)streamWriter:(EVStreamURLWriter*)writer gotResponseData:(NSData*)data {
    [data retain];
    dispatch_async(self.operationQueue, ^{
        [self.responseData appendData:data];
        [data release];
    });
}

- (void)streamWriter:(EVStreamURLWriter *)writer gotAnError:(NSError*)error {
    [error retain];
    dispatch_async(self.operationQueue, ^{
        [error autorelease];
        [self provider:self gotAnError:error];
        [self.dataProviderDelegate release];
        self.dataProviderDelegate = nil;
    });
}

- (void)streamWriterFinished:(EVStreamURLWriter *)writer {
    dispatch_async(self.operationQueue, ^{
        [self.dataProviderDelegate release];
        self.dataProviderDelegate = nil;
        NSError* error = nil;
        NSDictionary* json = [NSJSONSerialization JSONObjectWithData:self.responseData options:kNilOptions error:&error];
        if (error != nil) {
            [self provider:self gotAnError:error];
        } else {
            [self.delegate audioDataStreamerFinished:self withResponse:json];
        }
        [self.responseData setLength:0];
    });
}

@end