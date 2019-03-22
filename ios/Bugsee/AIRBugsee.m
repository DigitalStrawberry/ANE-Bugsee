/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Digital Strawberry LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#import "AIRBugsee.h"
#import "AIRBugseeAttachment.h"
#import "Functions/InitFunc.h"
#import "Functions/RelaunchFunc.h"
#import "Functions/LogErrorFunc.h"
#import "Functions/LogEventFunc.h"
#import "Functions/AddAttachmentFunc.h"
#import "Functions/SetAttributeFunc.h"
#import "Functions/ClearAttributeFunc.h"
#import "Functions/ClearAttributesFunc.h"
#import "Functions/LogToConsoleFunc.h"
#import "Functions/IsTestFlightFunc.h"
#import "Functions/StopFunc.h"
#import "Functions/ShowFeedbackControllerFunc.h"
#import "Functions/SetDefaultFeedbackGreetingFunc.h"

FREContext airBugseeExtContext = nil;
AIRBugsee* airBugseeSharedInstance = nil;

@implementation AIRBugsee {
    NSMutableArray<AIRBugseeAttachment*>* _attachments;
}

+ (nonnull AIRBugsee*) sharedInstance
{
    if(airBugseeSharedInstance == nil)
    {
        airBugseeSharedInstance = [AIRBugsee new];
    }
    return airBugseeSharedInstance;
}

- (id) init
{
    self = [super init];
    if(self != nil)
    {
        _attachments = [NSMutableArray array];
    }
    return self;
}

- (void) initWithToken:(nonnull NSString*) token options:(nullable NSDictionary *) options
{
    [self logToConsole:[NSString stringWithFormat:@"Initialize, options: %@", options]];
    
    [Bugsee launchWithToken:token andOptions:options];
    [Bugsee sharedInstance].delegate = self;
}

- (void) relaunchWithOptions:(nullable NSDictionary*) options
{
    [Bugsee relaunchWithDictionaryOptions:options];
}

- (void) logError:(nonnull NSString*) name code:(NSInteger) code params:(nullable NSDictionary*) params
{
    [self logToConsole:[NSString stringWithFormat:@"logError '%@' params = %@", name, params]];
    [Bugsee logError:[NSError errorWithDomain:name code:code userInfo:params]];
}

- (void) logEvent:(nonnull NSString*) name params:(nullable NSDictionary*) params
{
    [self logToConsole:[NSString stringWithFormat:@"logEvent '%@' params = %@", name, params]];
    if(params == nil)
    {
        [Bugsee registerEvent:name];
    }
    else
    {
        [Bugsee registerEvent:name withParams:params];
    }
}

- (void) addAttachment:(nonnull NSString*) name fileName:(nonnull NSString*) fileName filePath:(nonnull NSString*) filePath
{
    AIRBugseeAttachment* attachment = [AIRBugseeAttachment new];
    attachment.name = name;
    attachment.fileName = fileName;
    attachment.filePath = filePath;
    [_attachments addObject:attachment];
}

- (void) setAttribute:(nonnull NSString*) key value:(nonnull NSString*) value
{
    [self logToConsole:[NSString stringWithFormat:@"setAttribute (%@ -> %@)", key, value]];
    [Bugsee setAttribute:key withValue:value];
}

- (void) clearAttribute:(nonnull NSString*) key
{
    [self logToConsole:[NSString stringWithFormat:@"clearAttribute = %@", key]];
    [Bugsee clearAttribute:key];
}

- (void) clearAttributes
{
    [self logToConsole:@"clearAttributes"];
    [Bugsee clearAllAttributes];
}

- (void) stop
{
    [Bugsee stop:^{
        [self logToConsole:@"Stopped."];
    }];
}

- (void) logToConsole:(nonnull NSString*) message
{
    NSLog(@"[Bugsee] %@", message);
}

- (void) showFeedbackController
{
    [Bugsee showFeedbackController];
}

- (void) setDefaultFeedbackGreeting:(nonnull NSString*) greeting
{
    [Bugsee setDefaultFeedbackGreeting:greeting];
}

- (void) dispose
{
    [self stop];
    airBugseeSharedInstance = nil;
}

//
// MARK: Bugsee delegate
//

- (NSArray<BugseeAttachment *> *) bugseeAttachmentsForReport:(BugseeReport *) report
{
    if(_attachments.count > 0)
    {
        NSMutableArray<BugseeAttachment*>* result = [NSMutableArray array];
        for(AIRBugseeAttachment* a in _attachments)
        {
            [self logToConsole:[NSString stringWithFormat:@"Adding attachment: %@", a.name]];
            NSData* data = [NSData dataWithContentsOfFile:a.filePath];
            BugseeAttachment* attachment = [BugseeAttachment attachmentWithName:a.name filename:a.fileName data:data];
            [result addObject:attachment];
        }
        return result;
    }
    return @[];
}

- (void)bugsee:(Bugsee *)bugsee didReceiveNewFeedback:(NSArray<NSString *> *)messages {
    if(messages.count > 0)
    {
        NSMutableString* response = [NSMutableString string];
        for(NSString* message in messages)
        {
            if(response.length > 0)
            {
                [response appendString:@"||"];
            }
            [response appendString:message];
        }
        
        NSString* event = @"Bugsee::feedback";
        FREDispatchStatusEventAsync(airBugseeExtContext, (uint8_t*) [event UTF8String], (uint8_t*) [response UTF8String]);
    }
}

@end

//
// Context initialization
//

FRENamedFunction airBugseeExtFunctions[] =
{
    { (const uint8_t*) "init",              0, bsee_init },
    { (const uint8_t*) "relaunch",          0, bsee_relaunch },
    { (const uint8_t*) "logError",          0, bsee_logError },
    { (const uint8_t*) "logEvent",          0, bsee_logEvent },
    { (const uint8_t*) "logToConsole",      0, bsee_logToConsole },
    { (const uint8_t*) "addAttachment",     0, bsee_addAttachment },
    { (const uint8_t*) "setAttribute",      0, bsee_setAttribute },
    { (const uint8_t*) "clearAttribute",    0, bsee_clearAttribute },
    { (const uint8_t*) "clearAttributes",   0, bsee_clearAttributes },
    { (const uint8_t*) "isTestFlight",      0, bsee_isTestFlight },
    { (const uint8_t*) "stop",              0, bsee_stop },
    { (const uint8_t*) "showFeedbackController", 0, bsee_showFeedbackController },
    { (const uint8_t*) "setDefaultFeedbackGreeting", 0, bsee_setDefaultFeedbackGreeting }
};

void BugseeContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToSet, const FRENamedFunction** functionsToSet)
{
    *numFunctionsToSet = sizeof(airBugseeExtFunctions) / sizeof(FRENamedFunction);
    
    *functionsToSet = airBugseeExtFunctions;
    
    airBugseeExtContext = ctx;
}

void BugseeContextFinalizer(FREContext ctx)
{
    [[AIRBugsee sharedInstance] dispose];
}

void BugseeInitializer(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet)
{
    *extDataToSet = NULL;
    *ctxInitializerToSet = &BugseeContextInitializer;
    *ctxFinalizerToSet = &BugseeContextFinalizer;
}

void BugseeFinalizer(void* extData) { }







