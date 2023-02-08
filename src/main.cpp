/* XKCC is a cross-platform ChatKC client for desktop environments
Copyright (C) 2023 Alexander Hill

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.resize(640, 480);
    mainWindow.setWindowTitle("XKCC");
    // TODO: Create a menu bar for connecting to/disconnecting from servers, adjusting preferences, etc.
    // TODO: Create a row of tabs(one for each connected server)
    // TODO: Create a giant box for storing messages
    // TODO: Create a text box at the bottom for sending messages
    // TODO: Create a box to the side that shows a list of connected users
    mainWindow.show();
    return app.exec();
}