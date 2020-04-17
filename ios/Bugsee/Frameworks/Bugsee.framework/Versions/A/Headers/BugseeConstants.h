//
//  BugseeConstants.h
//  Bugsee
//
//  Created by ANDREY KOVALEV on 10.06.16.
//  Copyright © 2016 Bugsee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BugseeAttachment.h"

#define BugseeTrue @(YES)
#define BugseeFalse @(NO)

typedef enum : NSUInteger {
    /**
     * Low severity (lowest available)
     */
    BugseeSeverityLow = 1,
    /**
     * Medium severity
     */
    BugseeSeverityMedium = 2,
    /**
     * High severity
     */
    BugseeSeverityHigh = 3,
    /**
     * Critical
     */
    BugseeSeverityCritical = 4,
    /**
     * Blocker (highest available)
     */
    BugseeSeverityBlocker = 5
} BugseeSeverityLevel;

typedef enum : NSUInteger {
    /**
     *
     */
    BugseeFrameRateLow = 1,
    /**
     *
     */
    BugseeFrameRateMedium = 2,
    /**
     *
     */
    BugseeFrameRateHigh = 3
} BugseeFrameRate;

typedef enum : NSUInteger {
    BugseeStyleLight,
    BugseeStyleDusk,
    BugseeStyleBasedOnStatusBar,
    BugseeStyleSystem
} BugseeStyle;

typedef enum : NSUInteger {
    /**
     * Event is dispatched when Bugsee was successfully launched
     */
    BugseeLifecycleEventLaunched,
    /**
     * Event is dispatched when Bugsee is started after beling stopped
     */
    BugseeLifecycleEventStarted,
    /**
     * Event is dispatched when Bugsee is stopped
     */
    BugseeLifecycleEventStopped,
    /**
     * Event is dispatched when Bugsee recording is resumed after being paused
     */
    BugseeLifecycleEventResumed,
    /**
     * Event is dispatched when Bugsee recording is paused
     */
    BugseeLifecycleEventPaused,
    /**
     * Event is dispatched when Bugsee is launched and pending crash report is
     * discovered. That usually means that app was relaunched after crash.
     */
    BugseeLifecycleEventRelaunchedAfterCrash,
    /**
     * Event is dispatched before the reporting UI is shown
     */
    BugseeLifecycleEventBeforeReportShown,
    /**
     * Event is dispatched when reporting UI is shown
     */
    BugseeLifecycleEventAfterReportShown,
    /**
     * Event is dispatched when report is about to be uploaded to the server
     */
    BugseeLifecycleEventBeforeReportUploaded,
    /**
     * Event is dispatched when report was successfully uploaded to the server
     */
    BugseeLifecycleEventAfterReportUploaded,
    /**
     * Event is dispatched before the Feedback controller is shown
     */
    BugseeLifecycleEventBeforeFeedbackShown,
    /**
     * Event is dispatched after the Feedback controller is shown
     */
    BugseeLifecycleEventAfterFeedbackShown,
    /**
     * Event is dispatched before the bug/crash/error report assembly starts
     */
    BugseeLifecycleEventBeforeReportAssembled,
    /**
     * Event is dispatched after the bug/crash/error report assembly completes
     */
    BugseeLifecycleEventAfterReportAssembled
} BugseeLifecycleEventType;


@class BugseeNetworkEvent;
@class BugseeLogEvent;
@class BugseeExtendedReport;
typedef void (^BugseeEmptyBlock)(void);
typedef void (^BugseeStartedBlock)(BOOL success);
typedef void (^BugseeLogFilterDecisionBlock)(BugseeLogEvent * _Nullable event );
typedef void (^BugseeNetworkFilterDecisionBlock)(BugseeNetworkEvent * _Nullable event );
typedef void (^BugseeAttachmentsDecisionBlock)(NSArray<BugseeAttachment*>* _Nullable attachments);
typedef void (^BugseeNetworkEventFilterBlock)(BugseeNetworkEvent * _Nonnull event, BugseeNetworkFilterDecisionBlock _Nonnull decisionBlock);
typedef void (^BugseeExtendedReportBlock)(BugseeExtendedReport * _Nullable report);

/**
 *  BugseeStyleBasedOnStatusBarStyle setup style by current status bar style
 *  BugseeStyleDark when you have UIStatusBarStyleLightContent and BugseeStyleDefault when you have UIStatusBarStyleDefault
 */
extern NSString *const _Nonnull BugseeStyleSystemDefault,
                *const _Nonnull BugseeStyleDefault,
                *const _Nonnull BugseeStyleDark,
                *const _Nonnull BugseeStyleBasedOnStatusBarStyle
;

extern NSString *const _Nonnull BugseeShakeToReportKey,
                *const _Nonnull BugseeMaxRecordingTimeKey,
                *const _Nonnull BugseeScreenshotToReportKey,
                *const _Nonnull BugseeCrashReportKey,
                *const _Nonnull BugseeKillDetectionKey,
                *const _Nonnull BugseeFrameRateKey,
                *const _Nonnull BugseeMaxFrameRateKey,
                *const _Nonnull BugseeMinFrameRateKey,
                *const _Nonnull BugseeMonitorNetworkKey,
                *const _Nonnull BugseeMonitorWebSocketKey,
                *const _Nonnull BugseeStatusBarInfoKey,
                *const _Nonnull BugseeVideoEnabledKey,
                *const _Nonnull BugseeScreenshotEnabledKey,
                *const _Nonnull BugseeViewHierarchyEnabledKey,
                *const _Nonnull BugseeStyleKey,
                *const _Nonnull BugseeEnableMachExceptionsKey,
                *const _Nonnull BugseeEnableOnDeviceSymbolicationKey,
                *const _Nonnull BugseeReportPrioritySelectorKey,
                *const _Nonnull BugseeDefaultCrashPriorityKey,
                *const _Nonnull BugseeDefaultBugPriorityKey,
                *const _Nonnull BugseeCaptureLogsKey,
                *const _Nonnull BugseeWifiOnlyUploadKey,
                *const _Nonnull BugseeMaxDataSizeKey,
                *const _Nonnull BugseeVideoScaleKey,
                *const _Nonnull BugseeBuildTargetKey,
                *const _Nonnull BugseeBuildTypeKey,
                *const _Nonnull BugseeCaptureDeviceAndNetworkNames,
                *const _Nonnull BugseeMonitorBluetoothStatusKey,
                *const _Nonnull BugseeReportSummaryRequiredKey,
                *const _Nonnull BugseeReportDescriptionRequiredKey,
                *const _Nonnull BugseeReportEmailRequiredKey,
                *const _Nonnull BugseeReportLabelsEnabledKey,
                *const _Nonnull BugseeReportLabelsRequiredKey
;

/**
 *  We can only show you request/response bodies with size less than 5 kb
 */
extern NSString *const _Nonnull BugseeNetworkBodySizeTooLarge;

/**
 *  We support json, text and xml formats
 */
extern NSString *const _Nonnull BugseeNetworkBodyUnsupportedContentType;

/**
 *  No content type on request/response
 */
extern NSString *const _Nonnull BugseeNetworkBodyNoContentType;

/**
 *  We support data only in UTF8 string encoding
 */
extern NSString *const _Nonnull BugseeNetworkBodyCantReadData;

//Network event types, this constants are used in BugseeNetworkEvent bugseeNetworkEventType property.
//see documentation page to learn more https://docs.bugsee.com/sdk/ios/privacy/

extern NSString * const _Nonnull BugseeNetworkEventBegin;
extern NSString * const _Nonnull BugseeNetworkEventComplete;
extern NSString * const _Nonnull BugseeNetworkEventCancel;
extern NSString * const _Nonnull BugseeNetworkEventError;

extern NSString * const _Nonnull BugseeWebSocketEventOpen;
extern NSString * const _Nonnull BugseeWebSocketEventSend;
extern NSString * const _Nonnull BugseeWebSocketEventMessage;
extern NSString * const _Nonnull BugseeWebSocketEventClose;
extern NSString * const _Nonnull BugseeWebSocketEventError;

extern NSString * const _Nonnull BugseeReportTypeBug;
extern NSString * const _Nonnull BugseeReportTypeCrash;
extern NSString * const _Nonnull BugseeReportTypeError;


extern NSString * const _Nonnull BugseeAttachmentOverrideLabels;
