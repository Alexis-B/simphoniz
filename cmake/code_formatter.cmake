# Simphoniz - A Simple Photo Organizer
# Copyright (C) 2020  Erwan Grâce <erwan.grace@outlook.fr>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

find_program(CLANG_FORMAT_EXECUTABLE
             NAMES clang-format
             DOC "Path to clang-format executable.")

if(CLANG_FORMAT_EXECUTABLE)
    message(STATUS "clang-format found: ${CLANG_FORMAT_EXECUTABLE}")

    # Collect the files to format
    file(GLOB_RECURSE files src/*.cpp src/*.h include/*.h test/*.cpp test/*.h)

    # Formatting is automatically applied whenever the sources are compiled.
    add_custom_target(format ALL
                      COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${files}
                      COMMENT "Formatting code..."
                      VERBATIM)
endif()
