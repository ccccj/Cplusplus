#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <stdlib.h>

#define HEIGHT 10
#define WIDTH 20

// 地图
class Map
{
public:
    Map(){
        init_Map();
    }
    int random_num();
    void re_init();
    void setColor(int x, int y, int color);
    void setMapColor();
    void drawing();
    void de_drawing();
    bool can_change(int x, int y, int Mo[][4]);
    bool can_down();
    void clean_line();
    void pile();
    void rotate();
    void left();
    void right();
    bool down();
    void fall();
    void set_termio();
    void recover_termio();
    void get_char();
    void command();

private:
    struct Axis {
        int x;
        int y;
    } axis;
    int map[HEIGHT][WIDTH];
    int figure[7][4][4] = {
        /*
        0010 0100 0010 0110 0100 0010 0010
        0010 0100 0010 0110 0110 0110 0110
        0010 0110 0010 0000 0010 0100 0010
        0010 0000 0000 0000 0000 0000 0000
        */
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,1,1,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}
    };

    void init_Map();
    int num;

};

int Map::random_num() {
    return rand() % 7;
}

void Map::setMapColor() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            setColor(i, j, map[i][j]);
        }
    }
}

void Map::init_Map() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            map[i][j] = 47;
        }
    }
    printf("\033[2J"); // 清屏
    setMapColor();
    axis = {0, WIDTH / 2 - 2};
    num = random_num();
    for (int t = 0; t < 7; ++t) {
        int cl = rand() % 6 + 41;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (figure[t][i][j]) {
                    figure[t][i][j] = cl;
                }
            }
        }
    }
}

void Map::re_init() {
    num = random_num();
    axis = {0, WIDTH / 2 - 2};
    if (can_down() == 0) {
        printf("\033[2J"); // 清屏
        printf("game over\n");
        recover_termio();
        exit(0);
    }
}

void Map::setColor(int x, int y, int color) {
    /*=====================VT100=====================
    VT100的用法，参考自：
    https://blog.csdn.net/aiwangtingyun/article/details/79524899
    https://blog.csdn.net/liufei191010/article/details/81015445

    \033[0m		// 关闭所有属性
    \033[1m		// 设置为高亮
    \033[4m		// 下划线
    \033[5m		// 闪烁
    \033[7m		// 反显
    \033[8m		// 消隐
    \033[nA		// 光标上移 n 行
    \033[nB		// 光标下移 n 行
    \033[nC		// 光标右移 n 行
    \033[nD		// 光标左移 n 行

    \033[y;xH	// 设置光标位置

    \033[2J		// 清屏
    \033[K		// 清除从光标到行尾的内容
    \033[s		// 保存光标位置
    \033[u		// 恢复光标位置
    \033[?25l	// 隐藏光标
    \033[?25h	// 显示光标

    \033[30m – \033[37m 为设置前景色
    \033[40m – \033[47m 为设置背景色
    40:黑色; 41:红色; 42:绿色; 43: 黄色; 44:蓝色; 45:紫色; 46:青色; 47:白色;

    \033[41;36m something here \033[0m

    =====================VT100=====================*/
    ++x; // 第一行会没掉
    ++y;
    y *= 2; // 每个 y 占两格，所以乘 2

    printf("\033[%d;%dH", x, y); // \033[y;xH 设置光标位置
    // \033[40m  \033[40m将一个空格 背景变为黑色
    printf("\033[%dm\033[%dm  ", color, color);
    fflush(stdout);
    printf("\033[0m\033[0m"); // 恢复
    //printf("\033[?25l");
    printf("\033[30;0H");
}

void Map::drawing() {
    //printf("drawing();=============%d\n", axis.x);
    //printf("\033[2J"); // 清屏
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (figure[num][i][j]) setColor(axis.x + i, axis.y + j, figure[num][i][j]);
        }
    }
}

void Map::de_drawing() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (figure[num][i][j]) setColor(axis.x + i, axis.y + j, 47);
        }
    }
}

bool Map::can_change(int x, int y, int Mo[][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (Mo[i][j]
                && (x + i >= HEIGHT || y + j >= WIDTH || x + i < 0 || y + j < 0)) {
                return 0;
            }
            if (Mo[i][j] && map[x + i][y + j]-47) return 0;
        }
    }
    return 1;
}

bool Map::can_down() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (figure[num][i][j] && (axis.x+i+1 >= HEIGHT || axis.y+j >= WIDTH)) {
                return 0;
            }
            if (figure[num][i][j] && map[axis.x+i+1][axis.y+j]-47) return 0;
        }
    }
    return 1;
}

void Map::clean_line() {
    int i = HEIGHT - 1, flag, now = HEIGHT - 2;
    while (i > 0) {
        flag = 1;
        for (int j = 0; j < WIDTH; ++j) {
            if (map[i][j] == 47) {
                flag = 0;
                break;
            }
        }
        if (flag == 0) {
            --i;
            --now;
            continue;
        }
        for (int j = 0; j < WIDTH; ++j) {
            map[i][j] = map[now][j];
        }
        setMapColor();
        --now;
    }
    for (; i >= 0; --i) {
        for (int j = 0; j < WIDTH; ++j) {
            map[i][j] = 47;
        }
    }
    setMapColor();
}

void Map::pile() {
    if (can_down()) return;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (figure[num][i][j])
                map[axis.x + i][axis.y + j] = figure[num][i][j];
        }
    }
    setMapColor();
    re_init();
    clean_line();
}

void Map::rotate() {
    int B[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            B[j][4 - i - 1] = figure[num][i][j];
        }
    }
    if (can_change(axis.x, axis.y, B) == 0) return;

    de_drawing();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            figure[num][i][j] = B[i][j];
        }
    }
    drawing();
}

void Map::left() {
    if (can_change(axis.x, axis.y - 1, figure[num]) == 0)
        return;
    de_drawing();
    --axis.y;
    drawing();
}

void Map::right() {
    if (can_change(axis.x, axis.y + 1, figure[num]) == 0)
        return;
    de_drawing();
    ++axis.y;
    drawing();
}

bool Map::down() {
    if (can_down() == 0) return 0;
    de_drawing();
    ++axis.x;
    drawing();
    return 1;
}

void Map::fall() {
    // 到最底下
    while(can_down()) {
        ++axis.x;
    }
}

// 获取键盘输入
// 使用终端的非规范模式，缓存和编辑功能关闭
// ICANON处于复位状态，终端将字符当作普通字符处理，输入数据没有行的概念。
void Map::set_termio() {
    /*
    int tcgetattr(int fd, struct termios *termios_p);
    用于获取与终端相关的参数，成功返回零；失败返回非零

    参数fd为终端的文件描述符，返回的结果保存在termios结构体中，其中
    tcflag_t c_lflag
    c_lflag中ECHO宏（打开，输入了什么会显示在屏幕，所以要关闭）
    c_lflag中ICANON是规范模式（所以要关掉这个标志，就变成非规范模式）
    */
    struct termios t;
    tcgetattr(0, &t); // 0：标准输入
    t.c_lflag &= ~(ECHO | ICANON); // 关闭c_lflag中的ECHO和ICANON
    t.c_lflag &= ~ISIG;
    // 设置终端属性
    // int tcsetattr(int fd, int when, struct termios *info);
    tcsetattr(0, TCSANOW, &t); // TCSANOW 表示立即
}

void Map::recover_termio() {
    struct termios t;
    tcgetattr(0, &t); // 0：标准输入
    t.c_lflag |= ECHO | ICANON; // 打开c_lflag中的ECHO和ICANON

    // 设置终端属性
    // int tcsetattr(int fd, int when, struct termios *info);
    tcsetattr(0, TCSANOW, &t); // TCSANOW 表示立即
}

enum Direction {
    CHANGE = 65, // 方向键上
    DOWN = 66,
    RIGHT = 67,
    LEFT = 68,
    QUIT = 'q',
};

void Map::get_char() {
    fflush(stdin);
    char c = getchar();
    if (c == QUIT) {
        //printf("QUIT\n");
        recover_termio();
        exit(0);
    } else if (c == 27) {
        //printf("27===========\n");

        c = getchar();
        c = getchar();
        //c = getchar();
        //printf("%c\n", c);
        switch (c) {
            case CHANGE: rotate();break;
            case DOWN: fall(); break;
            case RIGHT: right(); break;
            case LEFT: left(); break;
        }
        pile();
    }
}

void Map::command() {
    // int timerfd_create(int clockid, int flags);
    // 创建一个新的timer对象 CLOCK_MONOTONIC(手动改时间不影响)
    int tfd = timerfd_create(CLOCK_MONOTONIC, 0);
    /*
    int timerfd_settime(int fd, int flags,
        const struct itimerspec *new_value,
        struct itimerspec *old_value);

    struct timespec {
        time_t tv_sec; // 秒
        long   tv_nsec; // 毫秒
    };

    struct itimerspec {
        struct timespec it_interval; //每隔多长时间超时
        struct timespec it_value; // 第一次超时时间
    };
    */

    struct itimerspec it = {{1, 0}, {1, 0}};
    timerfd_settime(tfd, 0, &it, NULL);
    // int timerfd_gettime(int fd, struct itimerspec *curr_value);
    while(1) {
        fd_set read_set; // 描述符集合 读集合
        FD_ZERO(&read_set); // 创建一个空的读集合
        FD_SET(STDIN_FILENO, &read_set); // 将标准输入描述符加入读集合
        FD_SET(tfd, &read_set);

        struct timeval tvl = {1, 0}; // 最多阻塞一秒
        // 阻塞，直到集合中某个描述符可以读
        select(tfd + 1, &read_set, NULL, NULL, &tvl);

        // FD_ISSET 判断哪个哪个描述符已经可以读了
        if (FD_ISSET(STDIN_FILENO, &read_set)) {
            //printf("aaaaaaaaaaaaaaaaaa\n");
            get_char();
        } else {
            //printf("?????????????\n");
            // tfd
            int ret = down();
            if (ret == 0) re_init();
            uint64_t data;
            read(tfd, &data, sizeof data);
            //printf("data: %d\n", data);
        }
    }
    close(tfd);

}


int main() {
    Map m;
    m.set_termio();
    m.drawing();
    m.command();
    m.recover_termio();
}














//
