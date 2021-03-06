/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020  Erwan Grâce <erwan.grace@outlook.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file CommandLineData.h
 * @author Erwan
 * @date 01/11/2019
 */

#ifndef SIMPHONIZ_COMMANDLINEDATA_H
#define SIMPHONIZ_COMMANDLINEDATA_H

#include <QtCore/QDir>

namespace simphoniz {

/**
 * @brief Holds the data present in the command line.
 * @ingroup console
 */
struct CommandLineData {
    QDir sourceDir;      ///< The source directory.
    QDir destinationDir; ///< The destination directory.
};

} // namespace simphoniz

#endif // SIMPHONIZ_COMMANDLINEDATA_H
