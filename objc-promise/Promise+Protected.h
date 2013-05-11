//
//  Promise+Protected.h
//  View Original
//
//  Created by Pete Hopkins on 5/10/13.
//  Copyright (c) 2013 Pete Hopkins. All rights reserved.
//

#import "Promise.h"

@interface Promise (Protected)
- (void)executeBlock:(bound_block)block;
@end
