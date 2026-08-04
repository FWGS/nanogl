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
	if conf.env.DEST_OS2 == 'android':
		conf.check_cc(lib='log')
	conf.define('NANOGL_MANGLE_PREPEND', 1)
	conf.define('REF_DLL', 1)
	# stub
	return

def build(bld):
	source = bld.path.ant_glob(['*.c'])
	libs = ['werror']
	if bld.env.DEST_OS2 == 'android':
		libs += ['LOG']
	includes = [ '.', 'GL/' ]

	bld.stlib(features = 'format',
		source   = source,
		target   = 'nanogl',
		includes = includes,
		use      = libs
	)

	if bld.env.TESTS:
		bld.program(features = 'test format',
			source = 'tests/test_batch.c',
			target = 'test_batch',
			includes = includes,
			use = ['nanogl'] + libs,
			install_path = None)
