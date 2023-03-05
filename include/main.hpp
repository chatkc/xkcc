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

#ifndef MAIN_HPP
#define MAIN_HPP

#include <vector>

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QTabWidget>

#include "channel.hpp"

class MainWindow : public QMainWindow {
public:
    MainWindow();
    ~MainWindow();

private:
    void addChannel(Channel *channel);
    void createActions();
    void createMenus();

    void aboutDialog();
    void connectServer();
    void disconnectServer();

    std::vector<Channel*> channels;

    QAction *aboutAction;
    QAction *connectAction;
    QAction *disconnectAction;
    QAction *pluginsAction;
    QAction *preferencesAction;
    QMenu *clientMenu;
    QMenu *serverMenu;
    QTabWidget *tabWidget;
};

#endif