#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define MYBUFSIZE 5
#define BEATS 4

#define A 2000	// 全音符
#define B (A / 2)	// 二分音符
#define C (A / 4) // 四分
#define D (A / 8)	// 八分
#define E (A / 16)	// 十六分
#define F (A / 32)	// 三十二分

//低音
#define L1
#define L2
#define L3
#define L4
#define L5
#define L6
#define L7
//高音
#define N1 532
#define N2 588
#define N3 660
#define N4 698
#define N5 784
#define N6 880
#define N7 988
//半弦音
#define H1 1046
#define H2 1175
#define H3 1319
#define H4 1397
#define H5 1568
#define H6 1760
#define H7 1976


int tones[] = {
        262,
        294,
        330,
        349,
        392,
        440,
        493,

        532,
        588,
        660,
        698,
        784,
};

void play(const vector<int>& vec) {
    for (auto num : vec) {
        Beep(tones[num], C);
    }
}

void eatline() {
    while (getchar() != '\n') {}
}

set<string> seq_set;
vector<vector<int>> seq_sorted;

void recur(int beats, vector<int> vec) {
    if (beats == 0) {
        string s;
        auto it = min_element(vec.begin(), vec.end());

        vector<int> tmp = vec;
        auto it2 = unique(tmp.begin(), tmp.end());
        vector<int> tmp2(tmp.begin(), it2);

        sort(tmp2.begin(), tmp2.end());

        for (auto& num : vec) {
            auto it3 = find(tmp2.begin(), tmp2.end(), num);
            s += to_string(it3 - tmp2.begin()) + " ";
        }
        s.pop_back();
        seq_set.insert(s);
        return;
    }
    vec.push_back(0);
    for (int i = 1; i <= BEATS; i++) {
        vec.back() = i;
        recur(beats - 1, vec);
    }

}

void getseq() {
    if (seq_set.size() != 0) {
        return;
    }

    recur(BEATS, vector<int>());
    for (auto ele : seq_set) {
        istringstream iss(ele);
        int num;
        vector<int> seq;
        while (iss >> num) {
            seq.push_back(num);
        }
        seq_sorted.push_back(seq);
    }
}

void enumerate() {
    getseq();
    cout << endl;
    cout << "穷举开始，共有 " << seq_sorted.size() << " 个音列" << endl;
    cout << "键入 [ / num ] 跳转到指定音列" << endl;
    cout << "键入 [ , ] 跳转前一个音列" << endl;
    cout << "键入 [ . ] 跳转下一个音列" << endl;
    cout << "键入 [ 回车 ] 重新播放" << endl;
    cout << "键入 [ quit ] 退出穷举" << endl;
    cout << endl;
    for (int i = 1; i <= seq_sorted.size(); ) {
        while (1) {
            cout << "音列 " << i << ": " << endl;

            for (auto num : seq_sorted[i - 1]) {
                cout << num + 1 << " ";
            }
            cout << endl;

            play(seq_sorted[i - 1]);
            char ch = getchar();
            if (ch != '\n') {
                ungetc(ch, stdin);
                break;
            }
        }
        string cmd;
        cin >> cmd;
        if (cmd == "/") {
            int num;
            if (cin >> num) {
                if (num < 1) {
                    i = 1;
                }
                else if (num > seq_sorted.size()) {
                    i = seq_sorted.size();
                }
                else {
                    i = num;
                }
            }
            else {
                cin.clear();
            }
        }
        else if (cmd == ",") {
            i = i > 1 ? i - 1 : 1;
        }
        else if (cmd == ".") {
            i = i < seq_sorted.size() ? i + 1 : seq_sorted.size();
        }
        else if (cmd == "quit") {
            break;
        }
        eatline();
    }
}

void emulate() {
    cout << endl;
    cout << "输入音列，非数字字符结尾 [ 1 2 3 4 # ] " << endl;
    cout << "输入 [ quit ] 退出" << endl;
    while (1) {
        vector<int> vec;
        int num;
        while (cin >> num) {
            vec.push_back(num);
        }
        cin.clear();
        string lineend;
        cin >> lineend;
        eatline();
        if (lineend == "quit") {
            return;
        }
        if (vec.empty()) {
            continue;
        }

        while (1) {
            play(vec);
            char ch = getchar();
            if (ch != '\n') {
                ungetc(ch, stdin);
                break;
            }
        }
    }

}

void practice() {
    cout << endl;
    cout << "听力训练开始" << endl;
    cout << "输入 [ quit ] 退出" << endl;
    cout << "输入 [ n ] 查看答案" << endl;
    cout << "输入 [ k ] 播放下一序列" << endl;

    while (1) {
        vector<int> vec;
        for (int i = 0; i < BEATS; i++) {
            int t = rand() % size(tones);
            vec.push_back(t);
        }

        while (1) {
            play(vec);
            char ch = getchar();
            if (ch == 'n') {
                for (auto num : vec) {
                    cout << num << " ";
                }
                cout << endl;
                eatline();
                continue;
            }
            if (ch != '\n') {
                ungetc(ch, stdin);
                break;
            }
        }
        string cmd;
        cin >> cmd;
        eatline();
        if (cmd == "quit") {
            return;
        }
    }
}

int main()
{
    // 6 4 1 6 6 4 6 6 8 6 1 4 #
    printf("Welcome to Acoustic Training (Version 0.0.1). Enter [ Ctrl^C ] to quit.\n");
    srand(time(NULL));
    while (1) {
        cout << endl;
        printf("请选择：\n");
        printf("1. 穷举音列\n");
        printf("2. 音列模拟\n");
        printf("3. 听力训练\n");
        printf("4. 音列试听\n");
        printf("5. 退出\n");

        string opt;
        cin >> opt;
        eatline();
        if (opt == "1") {
            enumerate();
        }
        else if (opt == "2") {
            emulate();
        }
        else if (opt == "3") {
            practice();
        }
        else if (opt == "4") {
            for (int i = 0; i < size(tones); i++) {
                Beep(tones[i], C);
            }
        }
        else if (opt == "5") {
            break;
        }
        else {
            printf("无效选择\n");
            continue;
        }
    }
    return 0;
}
