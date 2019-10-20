#!/bin/bash

clear
#clang-format-8 -i -sort-includes -style="{BasedOnStyle: Google, IndentWidth: 5, AlignConsecutiveAssignments: 'true', ColumnLimit: 150, AlignConsecutiveDeclarations: 'true'}" src/*.c inc/*.h
clang-format-8 -i -style=file src/*.c inc/*.h

