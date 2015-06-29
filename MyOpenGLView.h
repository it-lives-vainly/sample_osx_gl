// -*- mode: objc; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 *
 * create    : <2015-01-27 13:21:39 it_lives_vainly>
 * $Id$
 */
#ifndef __H_MYOPENGLVIEW__
#define __H_MYOPENGLVIEW__

#import <Cocoa/Cocoa.h>


@interface MyOpenGLView : NSOpenGLView
{
    NSTimer* timer_;
}

- (id)initWithFrame:(NSRect)frame_rect;
- (void)update;
- (void)drawRect:(NSRect)dirty_rect;

@end


#endif // __H_MYOPENGLVIEW__
//===
// EOF
//===
