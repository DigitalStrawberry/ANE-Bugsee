//
//  BugseeReport.h
//  Bugsee
//
//  Created by Dmitry Fink on 8/25/16.
//  Copyright © 2016 Bugsee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BugseeConstants.h"

@interface BugseeReport : NSObject
@property (nonatomic, strong) NSString * _Nonnull type;
@property (nonatomic) BugseeSeverityLevel severity;
@property (nonatomic, strong) NSArray<NSString*> * _Nullable labels;

@end
