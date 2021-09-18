/*
 * TikTakToe - a demo game using the snode.c framework
 * Copyright (C) 2020, 2021 Volker Christian <me@vchrist.at>
 * Copyright (C) 2021 Ertug Obalar, Jens Patzelt and Milad Tousi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TikTakToeSubProtocolFactory.h"

#include "TikTakToeGameModel.h"
#include "TikTakToeSubProtocol.h"

#include <web/http/server/SocketContextUpgradeFactorySelector.h>
#include <web/websocket/server/SocketContextUpgradeFactory.h>

#define NAME "tiktaktoe"

web::websocket::server::SubProtocol* TikTakToeSubProtocolFactory::create() {
    return new TikTakToeSubProtocol(NAME, TikTakToeGameModel::getGameModel());
}

TikTakToeSubProtocolFactory::TikTakToeSubProtocolFactory() {
    web::http::server::SocketContextUpgradeFactorySelector::instance()->add(new web::websocket::server::SocketContextUpgradeFactory(this));
}

void TikTakToeSubProtocolFactory::destroy() {
    delete this;
}

std::string TikTakToeSubProtocolFactory::name() {
    return NAME;
}

void TikTakToeSubProtocolFactory::destroy(web::websocket::server::SubProtocol* tikTakToeSubProtocol) {
    delete tikTakToeSubProtocol;
}

extern "C" {
    web::websocket::server::SubProtocolFactory* plugin() {
        return new TikTakToeSubProtocolFactory();
    }
}
