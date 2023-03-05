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

#include "channel.hpp"

Channel::Channel(Authentication *auth, QUrl *url) {
    this->auth = auth;
    sock = new QWebSocket();
    this->url = url;
    // Just making *sure* this connects to the correct port. ~Alex
    if(this->url->port() == -1) {
        this->url->setPort(2002);
    }
    sock->open(*url);
    script = luaL_newstate();
    // TODO: Initialize plugins for the channel
}

Channel::~Channel() {
    qDebug() << "Deleting channel: " << this->url->toString();
    lua_close(script);
    sock->close();
    delete auth;
    delete sock;
    delete url;
}

QString Channel::title() {
    return url->host();
}