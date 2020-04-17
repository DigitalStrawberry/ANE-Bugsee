//
//  BugseeOptions.h
//  Bugsee
//
//  Created by ANDREY KOVALEV on 13.09.2017.
//  Copyright © 2017 Bugsee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BugseeConstants.h"

@interface BugseeOptions : NSObject

+ (nullable BugseeOptions *) optionsFrom:(NSDictionary*_Nullable) options;
+ (nonnull BugseeOptions *) defaultOptions;

/**
 * Update with old style options.
 * example of usage:
 *
 * BugseeOptions * options = [BugseeOptions defaultOptions];
 * NSDictionary * dict =         options = @{BugseeMaxRecordingTimeKey   : @60,
                                             BugseeShakeToReportKey      : BugseeTrue,
                                             BugseeScreenshotToReportKey : BugseeTrue,
                                             BugseeStatusBarInfoKey      : BugseeTrue,
                                             ...
                                             BugseeCrashReportKey        : BugseeTrue
                                            };
 * [options updateWithOptions:dict];
 *
 * Keys for old style options you can find in BugseeConstants.h
 * Options documentation: https://docs.bugsee.com/sdk/ios/configuration/
 */
- (void)updateLaunchOptions:(nonnull NSDictionary*)dict;

/**
 * Use to change bugsee style to Light Dusk or Based on status bar
 * Default: BugseeStyleLight
 */
@property (nonatomic, assign) BugseeStyle bugseeStyle;

/**
 * Use this option to change frame rate to Low or High
 * Default: BugseeSeverityHigh
 */
@property (nonatomic, assign) BugseeFrameRate framerate;

/**
 * Priority for crashes
 * Default: BugseeSeverityBlocker
 */
@property (nonatomic, assign) BugseeSeverityLevel defaultCrashPriority;

/**
 * Priority for bugs
 * Default: BugseeSeverityHigh
 */
@property (nonatomic, assign) BugseeSeverityLevel defaultBugPriority;

/**
 * Shake gesture to trigger report
 * Default: NO
 */
@property (nonatomic, assign) BOOL shakeToReport;

/**
 * Screenshot key to trigger report
 * Default: YES
 */
@property (nonatomic, assign) BOOL screenshotToReport;

/**
 * Catch and report application crashes 
 * IOS allows only one crash detector to be active at a time, if you insist on using an 
 * alternative solution for handling crashes, you might want to use this option and disable 
 * Bugsee from taking over.
 * Default: YES
 */
@property (nonatomic, assign) BOOL crashReport;

/**
 Whether bug summary is required. If set to YES, then report form will prevent submission while
 summary field is empty.
 Default: NO
 */
@property (nonatomic, assign) BOOL reportSummaryRequired;

/**
 Whether bug description is required. If set to YES, then report form will prevent submission while
 description field is empty.
 Default: NO
 */
@property (nonatomic, assign) BOOL reportDescriptionRequired;

/**
 Whether email is required. If set to YES, then report form will prevent submission while
 email field is empty.
 Default: NO
 */
@property (nonatomic, assign) BOOL reportEmailRequired;

/**
 * Controls whether labels input field is available in bug reporting UI.
 * Default: NO
 */
@property (nonatomic, assign) BOOL reportLabelsEnabled;

/**
 * Controls whether Labels input field must be filled to submit data in bug reporting UI.
 * Default: NO
 */
@property (nonatomic, assign) BOOL reportLabelsRequired;

/**
 * Detect abnormal termination | experimental method, read more - https://docs.bugsee.com/sdk/ios/app-kills |
 * Default: NO
 */
@property (nonatomic, assign) BOOL killDetection;

/**
 * Capture network traffic
 * Default: YES
 */
@property (nonatomic, assign) BOOL monitorNetwork;

/**
 * Capture web-sockets traffic
 * Default: YES
 */
@property (nonatomic, assign) BOOL monitorWebSocket;

/**
 * Info about pending reports and current recording state.
 * Default: NO
 */
@property (nonatomic, assign) BOOL statusBarInfo;

/**
 * Enable video recording
 * Default: YES
 */
@property (nonatomic, assign) BOOL videoEnabled;

/**
 * Screenshot that appears in report
 * Default: When videoEnabled it's true, but if videoEnabled == false it's false
 */
@property (nonatomic, assign) BOOL screenshotEnabled;

/**
 * Value that when true, enables capturing of
 * views hierarchy upon bug reporting
 * Default: true
 */
@property (nonatomic, assign) BOOL viewHierarchyEnabled;

/**
 * experemental method may cause a deadlocks, be careful with using it.
 * Default: NO
 */
@property (nonatomic, assign) BOOL enableMachExceptions;

/**
* Enable on device symbolication for system frames.
* Default: YES
*/
@property (nonatomic, assign) BOOL enableOnDeviceSymbolication;

/**
 * Allow user to modify priority when reporting manual
 * Default: NO
 */
@property (nonatomic, assign) BOOL reportPrioritySelector;

/**
 * Automatically capture all console logs
 * Default: YES
 */
@property (nonatomic, assign) BOOL captureLogs;

/**
 * Maximum recording duration
 * Default: 60
 */
@property (nonatomic, assign) int maxRecordingTime;

/**
 * Bugsee network requests allowed only by wifi
 * Default: NO
 */
@property (nonatomic, assign) BOOL wifiOnlyUpload;

/**
 * Capture Device and wifi names.
 * They are shown on the issue screen.
 * Default: YES
 */
@property (nonatomic, assign) BOOL captureDeviceAndNetworkNames;

/**
 * Monitor current bluetooth status
 * NSBluetoothAlwaysUsageDescription info.plist flag needed in ios 13+ versions
 * Default: NO
 */
@property (nonatomic, assign) BOOL monitorBluetoothStatus;

/**
 * Bugsee will avoid using more disk space than specified. <br/>
 * Option has value of int type and should be specified in Mb. Value should not be smaller than 10.
 * Default: 50
 */
@property (nonatomic, assign) int maxDataSize;

/**
 *  Name of the project target
 */
@property (nonatomic, strong) NSString * _Nullable buildTarget;

/**
 *  debug, release, etc...
 */
@property (nonatomic, strong) NSString * _Nullable buildType;

@property (nonatomic, assign) uint maxFramerate;
@property (nonatomic, assign) uint minFramerate;

/**
 * Increase or decrease quality of video
 * Default: 0 - means not used
 */
@property (nonatomic, assign) float videoScale;

- (int) maxBodyDataLength;
- (nullable NSDictionary*) dictionary;
- (nullable id)objectForKeyedSubscript:(nonnull NSString*)key;

@end
