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

/** streamline into better solution
 * only use with luaL_dostring and luaL_dofile
 * */
bool lua_error_handler(lua_State* script, bool error) {
    if(error)
    {
        qCritical() << lua_tostring(script, -1);
        lua_pop(script, 1);
    }
    return error;
}

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
    init_plugins();

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
    // Basic sandboxing
    luaL_requiref(script, LUA_TABLIBNAME, luaopen_table, 1);
    lua_pop(script, 1);

    luaL_requiref(script, LUA_GNAME, luaopen_base, 1);
    lua_pop(script, 1);

    // all of this has been moved to base.lua
    // xkcc
    //lua_pushstring(script, "xkcc");
    //lua_createtable(script, 0, 1);
    // xkcc.hook
    //lua_pushstring(script, "hook");
    // This is equivalent to lua_createtable(script, 0, 0) anyways. ~Alex
    //lua_newtable(script);
    // TODO: More Lua API stuff ~Alex
    //lua_settable(script, -3);
}

void Channel::init_plugins() {
    // Allow possible customization later???? ~HW12Dev
    auto plugins_dir = QDir("plugins/");

    if (!plugins_dir.exists())
        plugins_dir.mkdir(".");

    // Abort if base.lua is not present
    if (!QFile(plugins_dir.absolutePath() + "/base.lua").exists())
    {
        qFatal("base.lua does not exist, please ensure it was bundled with your copy of this program or obtain a new one from https://github.com/chatkc/xkcc");
    }

    // always load base first
    qInfo() << "Loading base plugin";
    lua_error_handler(script, luaL_dofile(script, "plugins/base.lua"));

    foreach (QFileInfo info, plugins_dir.entryInfoList(QDir::Files))
    {
        if (info.fileName().endsWith(".lua") && info.baseName() != "base")
        {
            qInfo() << "Loading plugin: " << info.fileName();
            lua_error_handler(script, luaL_dofile(script, info.filePath().toStdString().c_str()));
        }
    }
}

QString Channel::title() {
    return url->host();
}