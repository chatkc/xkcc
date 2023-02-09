/* XKCC is a cross-platform ChatKC client for Qt-based desktop environments
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
#include <QMenuBar>

#include "main.hpp"

MainWindow::MainWindow() {
    createActions();
    createMenus();
    // TODO: Create a row of tabs(one for each connected server)
    // TODO: Create a giant box for storing messages
    // TODO: Create a text box at the bottom for sending messages
    // TODO: Create a box to the side that shows a list of connected users
    resize(640, 480);
    setWindowTitle("XKCC");
}

void MainWindow::createActions() {
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About XKCC"));
    // TODO: Connect the about action to a function
    connectAction = new QAction(tr("&Connect"), this);
    connectAction->setStatusTip(tr("Connects to a server"));
    // TODO: Connect the connect action to a function
    disconnectAction = new QAction(tr("&Disconnect"), this);
    disconnectAction->setStatusTip(tr("Disconnects from the current server"));
    // TODO: Connect the disconnect action to a function
    preferencesAction = new QAction(tr("&Preferences"), this);
    preferencesAction->setStatusTip(tr("Sets user preferences on the server"));
    // TODO: Connect the preferences action to a function
}

void MainWindow::createMenus() {
    serverMenu = menuBar()->addMenu(tr("&Server"));
    serverMenu->addAction(connectAction);
    serverMenu->addAction(disconnectAction);
    serverMenu->addSeparator();
    serverMenu->addAction(preferencesAction);
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}