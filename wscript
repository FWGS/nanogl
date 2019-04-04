#! /usr/bin/env python
# encoding: utf-8
# mittorn, 2018

from waflib import Logs
import os

top = '.'

def options(opt):
	# stub
	return

def configure(conf):
	conf.load('sdl2')
	conf.env.append_unique('DEFINES', '__MULTITEXTURE_SUPPORT__')
	conf.env.append_unique('DEFINES', 'XASH_SDL')
	conf.env.append_unique('DEFINES', 'NANOGL_MANGLE_PREPEND')
	# stub
	return

def build(bld):
	source = bld.path.ant_glob(['*.cpp'])
	libs = ['SDL2']
	includes = [ '.', 'GL/' ]

	bld.stlib(
		source   = source,
		target   = 'nanogl',
		features = 'cxx',
		includes = includes,
		use      = libs,
		install_path = bld.env.LIBDIR,
		subsystem = bld.env.MSVC_SUBSYSTEM
	)
