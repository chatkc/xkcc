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
    script = luaL_newstate();
    init_api();
    // TODO: Initialize plugins for the channel
    // Make sure we don't open a connection to the server before we're able to
    // handle requests! ~Alex
    sock->open(*url);
}

Channel::~Channel() {
    // qDebug() << "Deleting channel: " << this->url->toString();
    sock->close();
    lua_close(script);
    delete auth;
    delete sock;
    delete url;
}

void Channel::init_api() {
    // xkcc
    lua_pushstring(script, "xkcc");
    lua_createtable(script, 0, 1);
    // xkcc.hook
    lua_pushstring(script, "hook");
    // This is equivalent to lua_createtable(script, 0, 0) anyways. ~Alex
    lua_newtable(script);
    // TODO: More Lua API stuff ~Alex
    lua_settable(script, -3);
}

QString Channel::title() {
    return url->host();
}