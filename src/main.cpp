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
#include <QMessageBox>

#include "main.hpp"

MainWindow::MainWindow() {
    channels = {};
    createActions();
    createMenus();
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    // BLANK CHANNEL FOR TESTING ONLY ~Bread
    addChannel(new Channel(new Authentication(), new QUrl("chatkc://server.mattkc.com")));
    // TODO: Create a giant box for storing messages
    // TODO: Create a text box at the bottom for sending messages
    // TODO: Create a box to the side that shows a list of connected users
    resize(640, 480);
    setWindowTitle("XKCC");
}

MainWindow::~MainWindow() {
    // Channels
    for(Channel *chl : channels) {
        delete chl;
    }
    // delete channels;
    // Central Widget
    delete tabWidget;
    // Menus
    delete clientMenu;
    delete serverMenu;
    // Actions
    delete aboutAction;
    delete connectAction;
    delete disconnectAction;
    delete preferencesAction;
}

void MainWindow::openQtAboutDialog() {
    QMessageBox::aboutQt(this);
}

void MainWindow::aboutDialog() {
    QMessageBox *about = new QMessageBox(this);
    QPushButton *aboutQt = about->addButton("About Qt", QMessageBox::ActionRole);
    const QString licenseText = QMessageBox::tr(
        "<p>XKCC is a cross-platform ChatKC client for Qt-based desktop environments\n"
        "Copyright (C) %1 %2</p>\n"
        "<p>This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU Affero General Public License as published\n"
        "by the Free Software Foundation, either version 3 of the License, or\n"
        "(at your option) any later version.</p>\n"
        "<p>This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
        "GNU Affero General Public License for more details.</p>\n"
        "<p>You should have received a copy of the GNU Affero General Public License\n"
        "along with this program.  If not, see &lt;<a href=\"%3\" style=\"color:purple;\">%3</a>&gt;.</p>"
    ).arg(
        QStringLiteral("2023"),
        QStringLiteral("Alexander Hill"),
        QStringLiteral("https://www.gnu.org/licenses/")
    );
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->setWindowTitle(tr("About XKCC"));
    // TODO: We should put a summary at the top using `about->setText`. ~Alex
    about->setInformativeText(licenseText);
    about->setStandardButtons(QMessageBox::Ok);

    connect(aboutQt, &QPushButton::pressed, this, &MainWindow::openQtAboutDialog);
    about->exec();
}

void MainWindow::addChannel(Channel *channel) {
    channels.push_back(channel);
    tabWidget->addTab(channel, channel->title());
}

void MainWindow::connectServer() {
    // TODO: Create a popup window to collect the URL and authentication type
}

void MainWindow::disconnectServer() {
    int index = tabWidget->currentIndex();
    if(index == -1) {
        return;
    }
    auto widget = tabWidget->widget(index);
    tabWidget->removeTab(index);
    channels.erase(std::remove(channels.begin(), channels.end(), widget), channels.end());
    delete widget;
}

void MainWindow::openPluginsMenu() {
    //TODO: implement the plugins menu
}

void MainWindow::openPreferencesMenu() {
    //TODO: implement the preferences menu
}

void MainWindow::createActions() {
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About XKCC"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutDialog);
    connectAction = new QAction(tr("&Connect"), this);
    connectAction->setStatusTip(tr("Connects to a server"));
    connect(connectAction, &QAction::triggered, this, &MainWindow::connectServer);
    disconnectAction = new QAction(tr("&Disconnect"), this);
    disconnectAction->setStatusTip(tr("Disconnects from the current server"));
    connect(disconnectAction, &QAction::triggered, this, &MainWindow::disconnectServer);
    pluginsAction = new QAction(tr("&Plugins"), this);
    pluginsAction->setStatusTip(tr("Manages client plugins"));
    connect(pluginsAction, &QAction::triggered, this, &MainWindow::openPluginsMenu);
    preferencesAction = new QAction(tr("&Preferences"), this);
    preferencesAction->setStatusTip(tr("Sets user preferences on the server"));
    connect(preferencesAction, &QAction::triggered, this, &MainWindow::openPreferencesMenu);
}

void MainWindow::createMenus() {
    serverMenu = menuBar()->addMenu(tr("&Server"));
    serverMenu->addAction(connectAction);
    serverMenu->addAction(disconnectAction);
    serverMenu->addSeparator();
    serverMenu->addAction(preferencesAction);
    clientMenu = menuBar()->addMenu(tr("&Client"));
    clientMenu->addAction(pluginsAction);
    clientMenu->addAction(aboutAction);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Remove hardcoded dark and and allow users to set their own theme/completely customize their own ~HW12Dev
    app.setStyleSheet("QWidget {background-color: #1c1e1c;color: #b5b5b5;selection-background-color: #646665;border: 1px #000000;} QMessageBox QPushButton {color:#FFFFFF;border:1px solid #bfbfbf;padding:2px;} QMessageBox QPushButton:hover {color:#b5b5b5;}");

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}