# -*- mode: cmake; coding: utf-8-unix; tab-width: 4; -*-
cmake_minimum_required(VERSION 2.8)

set(TARGET_NAME OSXCMakeAppGL)
project(${TARGET_NAME})

set(SRC_FILES
  main.mm
  AppDelegate.h
  AppDelegate.m
  MyOpenGLView.h
  MyOpenGLView.mm
  simple_gl_triangle.h
  simple_gl_triangle.cc)

add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SRC_FILES})

include_directories ( /System/Library )
find_library(OPENGL_LIBRARY OpenGL)
find_library(COCOA_LIBRARY Cocoa)
find_library(APPKIT_LIBRARY AppKit)
find_library(WEBKIT_LIBRARY WebKit)

find_library(APP_SERVICES_LIBRARY ApplicationServices )
mark_as_advanced (COCOA_LIBRARY
  APPKIT_LIBRARY
  WEBKIT_LIBRARY
  APP_SERVICES_LIBRARY)
set(EXTRA_LIBS ${COCOA_LIBRARY} ${APPKIT_LIBRARY} ${APP_SERVICES_LIBRARY} ${OPENGL_LIBRARY} ${WEBKIT_LIBRARY})
target_link_libraries(${TARGET_NAME} ${EXTRA_LIBS})

set_property (TARGET ${TARGET_NAME} APPEND_STRING PROPERTY
              COMPILE_FLAGS "-fobjc-arc")

set(MACOSX_BUNDLE_EXECUTABLE "${TARGET_NAME}")
set(MACOSX_BUNDLE_INFO_STRING "${TARGET_NAME}")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.example")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_NAME} Version ${VERSION}")
set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION})
set(MACOSX_BUNDLE_BUNDLE_VERSION ${VERSION})
set(MACOSX_BUNDLE_COPYRIGHT "Copyright 2013.")
set(MACOSX_BUNDLE_NSMAIN_NIB_FILE "")
set(MACOSX_BUNDLE_NSPRINCIPAL_CLASS "NSApplication")

set_target_properties(${TARGET_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST Info-CMake.plist)

#===
# EOF
#===