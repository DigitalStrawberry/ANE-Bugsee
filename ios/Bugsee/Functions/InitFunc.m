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
#import "InitFunc.h"
#import <AIRExtHelpers/MPFREObjectUtils.h>

FREObject bsee_init( FREContext context, void* functionData, uint32_t argc, FREObject argv[] ) {
    NSString* token = [MPFREObjectUtils getNSString:argv[0]];
    NSDictionary* options = nil;
    if(argv[1] != nil)
    {
        NSString* jsonStr = [MPFREObjectUtils getNSString:argv[1]];
        if(jsonStr != nil)
        {
            NSData* jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
            NSError* error = nil;
            id json = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:&error];
            if(error == nil && json != nil && [json isKindOfClass:[NSDictionary class]])
            {
                options = (NSDictionary*) json;
            }
        }
    }
    
    [[AIRBugsee sharedInstance] initWithToken:token options:options];
    return nil;
}
