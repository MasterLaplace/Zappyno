#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# File name: gen_ninja.py
# Author: MasterLaplace

import os

TOP_FILE = """#
#! FLAGS
#
cxx = g++
cuda_cxx = nvcc
gpp_cflags = -std=c++17 -Wall -Wextra -pthread -g3 -ggdb -pg
nvcc_cflags = -std=c++17
opti = -Ofast -march=native -flto -pipe
ldflags = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lconfig -pthread
cuda_flags = --compiler-options -fPIC -Xcompiler -rdynamic

#
#! RULES
#
rule compile
 command = $cxx -D CUDA_ENABLED $gpp_cflags $opti -I $includes -c $in -o $out
 description = Compiling $out

rule link
  command = $cxx $in $ldflags -o $out
  description = Linking $out

#
#! BUILDS
#
"""

FOOT_FILE = """#
#! BUILD TARGETS
#
build zappy_gui: link %s
"""

cpp_files = []
obj_src_files = []

for root, _, files in os.walk('./'):
    for file in files:
        if file.endswith('.cpp'):
            filepath = os.path.join(root, file)
            cpp_files.append(filepath)

if os.path.exists('build.ninja'):
  os.remove('build.ninja')

with open('build.ninja', 'w') as f:
	f.write(TOP_FILE)
	for cpp_file in cpp_files:
		obj_file = os.path.splitext(cpp_file)[0].replace('./', 'obj/') + '.o'
		obj_src_files.append(obj_file)
		include_path = os.path.dirname(cpp_file)
		f.write(f'build {obj_file}: compile {cpp_file}\n')
		f.write(f' includes = {include_path}\n\n')

	f.write(FOOT_FILE % (' '.join(obj_src_files)))
