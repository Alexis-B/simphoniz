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
 * @file main.cpp
 * @author Erwan
 * @date 21/09/2019
 */

#include <cstdio>
#include <iostream>

#include <simphoniz/Application.h>
#include <simphoniz/io/console/CommandLineData.h>
#include <simphoniz/io/console/CommandLineParser.h>
#include <simphoniz/io/console/ProgressBar.h>
#include <simphoniz/io/photo/PhotoDirectoryParser.h>
#include <simphoniz/log/LogManager.h>
#include <simphoniz/photo/PhotoDirectory.h>
#include <simphoniz/processing/PhotoCounter.h>
#include <simphoniz/processing/PhotoSorter.h>

using namespace simphoniz;

namespace {

const auto COPYRIGHT_NOTICE = "Simphoniz  Copyright (C) 2020  Erwan Grâce\n"
                              "This is free software; see the source code for copying conditions.\n"
                              "There is ABSOLUTELY NO WARRANTY; not even for MERCHANTABILITY or\n"
                              "FITNESS FOR A PARTICULAR PURPOSE.\n\n";

} // namespace

int main(int argc, char** argv)
{
    Application app{argc, argv};

    Q_UNUSED(app)

    /********************************************
     * Parse the command line
     ********************************************/
    CommandLineParser parser;
    auto data = CommandLineData{};
    auto errorMessage = QString{};
    switch (parser.doParsing(data, errorMessage)) {
        case CommandLineParsingResult::OK:
            break;
        case CommandLineParsingResult::KO:
            fputs(qPrintable(errorMessage), stderr);
            fputs("\n\n", stderr);
            fputs(qPrintable(parser.helpText()), stderr);
            return 1;
        case CommandLineParsingResult::VERSION_REQUESTED:
            printf("%s %s\n", qPrintable(Application::applicationName()),
                   qPrintable(Application::applicationVersion()));
            return 0;
        case CommandLineParsingResult::HELP_REQUESTED:
            parser.showHelp();
    }

    std::cout << COPYRIGHT_NOTICE;

    /********************************************
     * Initialize the logging system
     ********************************************/
    LogManager::getInstance().initialize();

    /********************************************
     * Search for the photos to sort
     ********************************************/
    std::cout << "Analyzing directory " << data.sourceDir.absolutePath().toStdString() << "..."
              << std::endl;
    const auto photoDir = PhotoDirectoryParser{}.execute(data.sourceDir);
    if (!photoDir) {
        std::cerr << "No photo found!" << std::endl;
        return 1;
    }

    /********************************************
     * Process the photo files
     ********************************************/
    PhotoCounter counter;
    photoDir->accept(counter);
    const auto count = counter.getCount();

    std::cout << "Processing " << count << " photo(s)..." << std::endl;

    PhotoSorter sorter{data.destinationDir};
    ProgressBar progressBar{count};

    QObject::connect(&sorter, &PhotoSorter::photoSorted, &progressBar, &ProgressBar::update);

    photoDir->accept(sorter);

    return 0;
}
