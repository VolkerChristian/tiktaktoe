/*
 * tiktaktoe - a game using SnodeC
 * Copyright (C) 2021 Volker Christian <me@vchrist.at>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
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

#ifndef TIKTAKTOESUBPROTOCOL_H
#define TIKTAKTOESUBPROTOCOL_H

class TikTakToeGameModel;

//#include <net/timer/IntervalTimer.h>
#include <web/websocket/server/SubProtocol.h>

namespace net::timer {
    class Timer;
} // namespace net::timer

class TikTakToeSubProtocol : public web::websocket::server::SubProtocol {
public:
    TikTakToeSubProtocol(const std::string& name, TikTakToeGameModel& game);

    ~TikTakToeSubProtocol() override;

    void onConnected() override;
    void onMessageStart(int opCode) override;
    void onMessageData(const char* junk, std::size_t junkLen) override;
    void onMessageEnd() override;
    void onMessageError(uint16_t errnum) override;
    void onPongReceived() override;
    void onDisconnected() override;

private:
    bool activePlayer = false;

    std::string data;

    int flyingPings = 0;

    const std::string name;

    TikTakToeGameModel& gameModel;

    net::timer::Timer& timer;
};

#endif // TIKTAKTOESUBPROTOCOL_H
