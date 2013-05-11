//
//  Promise.h
//  objc-promise
//
//  Created by Michael Roberts on 2012-10-12.
//  Copyright (c) 2012 Mike Roberts. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^bound_block)(void);

@class Deferred;
@class DispatchPromise;
@class Promise;

typedef void (^resolved_block)(id result);
typedef void (^rejected_block)(NSError *error);
typedef void (^any_block)(void);

typedef enum {
    Incomplete = 0,
    Rejected   = 1,
    Resolved   = 2
} PromiseState;

@protocol Promise <NSObject>

@property (readonly) id result;
@property (readonly) NSError *reason;
@property (readonly) BOOL isResolved;
@property (readonly) BOOL isRejected;

- (Promise *)when:(resolved_block)resolvedBlock;
- (Promise *)failed:(rejected_block)rejectedBlock;
- (Promise *)any:(any_block)anyBlock;
- (Promise *)when:(resolved_block)whenBlock failed:(rejected_block)rejectedBlock;
- (Promise *)when:(resolved_block)whenBlock failed:(rejected_block)rejectedBlock any:(any_block)anyBlock;

- (Promise *)on:(dispatch_queue_t)queue;
- (Promise *)onMainQueue;

- (Promise *)timeout:(NSTimeInterval)interval;
@end

@interface Promise : NSObject <Promise> {
    NSMutableArray *_callbackBindings;
    dispatch_queue_t _queue;
    
    NSObject *_stateLock;
    PromiseState _state;
    
    id _result;
    NSError *_reason;
}

+ (Promise *)resolved:(id)result;
+ (Promise *)rejected:(NSError *)reason;

+ (Promise *)or:(NSArray *)promises;
+ (Promise *)and:(NSArray *)promises;

@end
