//
// Created by shiqi on 2019-08-06.
//

#ifndef INC_2D_ANIMATION_ACONTROLLER_H
#define INC_2D_ANIMATION_ACONTROLLER_H

#include <queue>
#include <vector>
#include "AEntity.h"
#include "AnimationSet.h"

class AController : public Controller {

private:
    Player* player;
    int playerStatus;
    std::queue<std::bitset<256>> q;
    std::queue<int> pos;

public:
    AController() {
        player = new Player(this);
        playerStatus = 0;
    }

    void notify(int command) {

        if (playerStatus == 0) {
            /* player is still */
            if (command == 1) {
                // WALK
                std::cout << "start walk" << std::endl;
                auto data = startWalk().getData();
                auto data2 = startWalk().getData2();
                for(int i = 0; i < data.size(); i++) {
                    q.push(data[i]);
                    pos.push(player->getX() + data2[i]);
                }

                playerStatus = 1;
            } else if (command == 2) {
                // JUMP
                auto data = jump().getData();
                for(int i = 0; i < data.size(); i++) {
                    q.push(data[i]);
                }
                playerStatus = 2;
            }
        } else if (playerStatus == 1) {
            /* player is walking */
            if (command == 1) {
                //WALK
                std::cout << "keep walking" << std::endl;
                auto data = walking().getData();
                auto data2 = walking().getData2();
                for(int i = 0; i < data.size(); i++) {
                    pos.push(player->getX() + data2[i]);
                    q.push(data[i]);
                }
            } else if (command == 0) {
                std::cout << "stop walk" << std::endl;
                auto data = stopWalk().getData();
                auto data2 = stopWalk().getData2();
                for(int i = 0; i < data.size(); i++) {
                    pos.push(player->getX() + data2[i]);
                    q.push(data[i]);
                }
                playerStatus = 0;
            } else if (command == 2) {
                //WALK JUMP
//                auto data = startWalk().mix(jump()).getData();
//                for(int i = 0; i < data.size(); i++) {
//                    q.push(data[i]);
//                }
            }
        } else if(playerStatus == 2) {
            if(command == 0) {
                q.push(player->getFigure());
            }
            playerStatus = 0;
        }
    }


    void handle(char input) {
        switch(input) {
            case 'w':
                player->setX(2);
                break;
            case 'd':
                player->setX(1);
                break;
            default:
                player->setX(0);
        }
    }

    std::bitset<256> getPlayerDraw() {
        std::bitset<256> data = q.front();
        return data;
    }

    std::bitset<256> getPlayerDynamic() {

        if(q.empty()) {

            return player->getFigure();
        }

        if(!q.empty()) {
            std::bitset<256> data = q.front();

            q.pop();

            return data;
        }
    }

    int getPlayerX() {
        if(pos.empty()) {

            return player->getX();

        } else {
            int x = pos.front();

            pos.pop();

            return x;
        }

    }
};
#endif //INC_2D_ANIMATION_ACONTROLLER_H
