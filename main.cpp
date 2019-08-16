#include <iostream>
#include <unistd.h>
#include <list>
#include "Entity.h"
#include "AController.h"
#include <termios.h>
#include <unistd.h>
#include <thread>


std::condition_variable cv;
std::mutex mtx;
int ch;
bool INPUT_SIGNAL = false;


struct Engine {
    bool isWindowExit;
    bool isEchoOn;
    bool isBlock;
    AController controller;

public:
    void init() {
        isWindowExit = false;
        isEchoOn = true;
        isBlock = false;
    }

    void mainloop() {
        struct termios oldt, newt;

        tcgetattr ( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );

        std::thread worker = std::thread([this]{timer(200);});

        while(!isWindowExit) {
            tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
            ch = getchar();
            tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

            INPUT_SIGNAL = true;

            cv.notify_one();
        }

        worker.join();
    }

    void timer(int period) {
        while(!isWindowExit) {

            std::unique_lock<std::mutex> lck(mtx);

            cv.wait_for(lck, std::chrono::milliseconds(period), []{return INPUT_SIGNAL;});

            if(INPUT_SIGNAL) {
                INPUT_SIGNAL = false;
                dispatch(ch);
            } else {
                dispatch(0);
            }
        }
        printf("Bye!\n");
    }

//
//    void run() {
//        char c;
//
//        //drawStatic();
//
//        while(c = getchar()) { // 设置成阻塞模式
//            dispatch(c);
//
//            if(isWindowExit) {
//                printf("Bye!\n", c);
//                break;
//            }
//        }
//    }

    void dispatch(char c) {
        if (isEchoOn) {
            printf("%c\n", c);
        }
        if (c == 'q') {
            isWindowExit = true;
        }

        if (c != '\n') {
            controller.handle(c);

            drawDyanmic();
        }
    }


    void drawDyanmic() {
//        draw(world.getWorld);

        draw(controller.getPlayerDynamic(), controller.getPlayerX());
    }

    void draw(std::bitset<256> figure, int x) {

        for(int i = 15; i >= 0; i--) {
            for(int k = 0; k < x; k++) {
                std::cerr << " ";
            }
            for(int j = 15; j >= 0; j--) {
                std::cerr << figure[i*16 + j];
            }
            std::cerr << "\n";
        }
    }
};


int main() {
    Engine engine;
    engine.mainloop();
}