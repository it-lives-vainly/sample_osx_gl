// -*- mode: objc; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 *
 * create    : <2015-02-14 16:31:35 it_lives_vainly>
 * $Id$
 */

#import "AppDelegate.h"
#import "MyOpenGLView.h"
#import "WebKit/WebKit.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSRect frame_rect = NSMakeRect(100, 100, 400, 400);

    MyOpenGLView* gl_view = [[MyOpenGLView alloc]initWithFrame:frame_rect];

    // View をオーバーレイさせるときには setWantsLayer に YES を指定
    [gl_view setWantsLayer:YES];
    [self.window setContentView:gl_view];

    // オーバーレイする View の作成
    NSRect text_rect = NSMakeRect(0, 0, 200, 200);

    WebView* web_view = [[WebView alloc] initWithFrame:text_rect frameName:@"a" groupName:@"b"];

    NSURL* ns_url = [NSURL URLWithString:@"http://www.yahoo.co.jp"];
    NSURLRequest* ns_req = [NSURLRequest requestWithURL:ns_url];
    [[web_view mainFrame] loadRequest:ns_req];

    [gl_view addSubview:web_view];

}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

@end
