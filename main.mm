// -*- mode: objc; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 *
 * create    : <2015-06-22 19:14:11 it_lives_vainly>
 * $Id$
 */
#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

int main(int argc, const char * argv[]) {

    [NSApplication sharedApplication];

    // Create a window:

    NSUInteger windowStyle = (NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask);

    NSRect windowRect = NSMakeRect(100, 100, 400, 400);
    NSWindow * window = [[NSWindow alloc] initWithContentRect:windowRect
                                                    styleMask:windowStyle
                                                      backing:NSBackingStoreBuffered
                                                        defer:NO];

    NSWindowController * windowController = [[NSWindowController alloc] initWithWindow:window];

    AppDelegate* app_delegate = [[AppDelegate alloc] init];
    [[NSApplication sharedApplication] setDelegate:app_delegate];
    app_delegate.window = window;

    // TODO: メニューなどはここで追加する(QUIT 等)

    [window orderFrontRegardless];
    [NSApp run];

    return (0);
}




//===
// EOF
//===
