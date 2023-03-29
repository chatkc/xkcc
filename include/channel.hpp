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

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <lua.hpp>

#include <QUrl>
#include <QWebSocket>
#include <QWidget>
#include <QDir>

#include "authentication.hpp"

class Channel : public QWidget {
public:
    Channel(Authentication *auth, QUrl *url);
    ~Channel();

    QString title();

private:
    Authentication *auth;
    lua_State *script;
    QWebSocket *sock;
    QUrl *url;

    void init_api();
    void init_plugins();
};

#endif