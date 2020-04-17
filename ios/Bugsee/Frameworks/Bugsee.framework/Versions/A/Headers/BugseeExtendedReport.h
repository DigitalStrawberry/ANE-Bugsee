//
//  BugseeExtendedReport.h
//  Bugsee
//
//  Created by Alexey Karimov on 4/15/19.
//  Copyright © 2019 Bugsee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BugseeConstants.h"

/**
 * Bug report that can be filled with data before uploading to
 * Bugsee servers. Used with @c[Bugsee createReport] and
 * @c[Bugsee uploadReport]
 */
@interface BugseeExtendedReport : NSObject

/**
 * Short summary of the report
 *
 * @return NSString
 */
@property (nonatomic, strong, readonly) NSString * _Nullable summary;
/**
 * Detailed descirption of the report
 *
 * @return NSString
 */
@property (nonatomic, strong, readonly) NSString * _Nullable reportDescription;
/**
 * Screenshot captured for the report.
 
 * @return UIImage if scrrenshot capturing was enabled via launch options. Otherwise nil.
 */
@property (nonatomic, strong, readonly) UIImage * _Nullable screenshot;
/**
 * Array containing all the associated labels
 *
 * @return NSArray<NSString*>
 */
@property (nonatomic, strong) NSArray<NSString*> * _Nullable labels;
/**
 * Dictinonary containing all the attributes for this report
 *
 * @return NSDictionary
 */
@property (nonatomic, strong, readonly) NSDictionary * _Nonnull attributes;
/**
 * Flag that indicates whether screenshot was changed. This flag is set
 * when @c[report setScreenshot] is called.
 */
@property (nonatomic, assign, readonly) BOOL isScreenshotChanged;
/**
 * Severity if this bug report
 */
@property (nonatomic, assign, readonly) BugseeSeverityLevel severity;

/**
 * Sets the summary for this report
 *
 * @param summary String containing the summary for this report
 */
- (void)setSummary:(NSString* _Nullable)summary NS_SWIFT_NAME(setSummary(_:));
/**
 * Sets detailed description for that report
 *
 * @param description String containing the detailed description for this report
 */
- (void)setDescription:(NSString* _Nullable)description NS_SWIFT_NAME(setDescription(_:));
/**
 * Sets/replaces the screenshot for this report. You can also check
 * the isScreenshotChanged
 *
 * @param screenshot Screenshot to asisgn to this report
 */
- (void)setScreenshot:(UIImage* _Nullable)screenshot NS_SWIFT_NAME(setScreenshot(_:));
/**
 * Sets the attibute for this report. Note, that it will not be set
 * globally, unlike when you call @c[Bugsee setAttribute]
 *
 * @param key Name for the attribute
 * @param value Value of the attribute
 */
- (void)setAttribute:(NSString* _Nonnull)key withValue:(id _Nonnull )value NS_SWIFT_NAME(setAttribute(_:value:));
/**
 * Removes an attribute with the specified name
 *
 * @param key Attribute name to delete by
 */
- (void)clearAttribute:(NSString* _Nonnull)key NS_SWIFT_NAME(clearAttribute(_:));
/**
 * Removes all the attributes from this report. Note, that this will remove
 * only attributes set directly on this report instance. Global attributes
 * set by @c[Bugsee setAttribute] will not be affected.
 */
- (void)clearAllAttributes NS_SWIFT_NAME(clearAllAttributes());
/**
 * Sets the severity of this bug report
 *
 * @param severity Severity level of bug report
 */
- (void)setSeverity:(BugseeSeverityLevel)severity NS_SWIFT_NAME(setSeverity(_:));

@end

