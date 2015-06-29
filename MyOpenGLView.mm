// -*- mode: objc; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 *
 * create    : <2015-01-27 16:34:11 it_lives_vainly>
 * $Id$
 */
#include "MyOpenGLView.h"

#include <OpenGL/gl3.h>
#include "simple_gl_triangle.h"

@implementation MyOpenGLView

- (id)initWithFrame:(NSRect)frame_rect
{

    static const NSOpenGLPixelFormatAttribute attr[]= {
        NSOpenGLPFANoRecovery,
        NSOpenGLPFADoubleBuffer,
        //NSOpenGLPFAWindow,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAColorSize,  24,
        NSOpenGLPFAAlphaSize,   8,
        NSOpenGLPFADepthSize,  24,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        0
    };

    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    self = [super initWithFrame:frame_rect pixelFormat:pixelFormat];

    if (self != nil) {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(_surfaceNeedsUpdate:)
                                                     name:NSViewGlobalFrameDidChangeNotification
                                                   object:self];

        timer_ = [NSTimer timerWithTimeInterval:1.0/60.0
                                         target:self
                                     selector:@selector(update)
                                       userInfo:self
                                        repeats:true];
        if (timer_) {
            [[NSRunLoop currentRunLoop] addTimer:timer_ forMode:NSRunLoopCommonModes];
        }
    }
    return self;
}

- (void)update
{
    [self drawRect:NSMakeRect(0, 0, 200, 200)];
}

- (void)drawRect:(NSRect)dirty_rect
{
    NSOpenGLContext* context = [self openGLContext];
    [context makeCurrentContext];

    gl_sample::TestDraw();

    [context flushBuffer];
}


@end


//===
// EOF
//===
