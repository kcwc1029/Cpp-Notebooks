// 專案：黑暗森林 - 文字冒險遊戲
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    int job;
    int attack, magic, agility;

    cout << "╔══════════════════════════════╗" << endl;
    cout << "║     黑暗森林 - 文字冒險      ║" << endl;
    cout << "╚══════════════════════════════╝" << endl;
    cout << "\n請輸入你的名字：";
    getline(cin, name);

    cout << "\n請選擇職業：" << endl;
    cout << "1. 戰士（攻擊+3，魔法-1，敏捷+0）" << endl;
    cout << "2. 法師（攻擊-1，魔法+3，敏捷+0）" << endl;
    cout << "3. 盜賊（攻擊+0，魔法-1，敏捷+3）" << endl;
    cout << "選擇：";
    cin >> job;

    string jobName;
    if (job == 1) {
        jobName = "戰士"; attack = 8; magic = 2; agility = 5;
    } else if (job == 2) {
        jobName = "法師"; attack = 4; magic = 9; agility = 5;
    } else if (job == 3) {
        jobName = "盜賊"; attack = 5; magic = 2; agility = 9;
    } else {
        cout << "無效選擇，預設為戰士。" << endl;
        jobName = "戰士"; attack = 8; magic = 2; agility = 5; job = 1;
    }

    cout << "\n歡迎，" << jobName << " " << name << "！" << endl;
    cout << "能力值 → 攻擊：" << attack << "  魔法：" << magic << "  敏捷：" << agility << endl;

    // 節點 1
    cout << "\n════════════════════════════════" << endl;
    cout << "你站在黑暗森林的入口。" << endl;
    cout << "前方有一條筆直的主路，樹叢中隱約可見一條小徑。" << endl;
    cout << "\n你選擇：" << endl;
    cout << "1. 走主路，正面突破" << endl;
    cout << "2. 走小徑，秘密繞行" << endl;
    cout << "選擇：";

    int choice1;
    cin >> choice1;
    while (choice1 != 1 && choice1 != 2) {
        cout << "無效選擇，請輸入 1 或 2：";
        cin >> choice1;
    }

    if (choice1 == 1) {
        if (job == 1) cout << "\n你的戰士體魄讓你輕鬆穿越荊棘，" << endl;
        else          cout << "\n荊棘刮破了你的衣物，但你還是穿越了，" << endl;
        cout << "深處，一頭巨龍擋住了你的去路！" << endl;

        cout << "\n龍發出震耳欲聾的咆哮！" << endl;
        cout << "你選擇：" << endl;
        cout << "1. 拔出武器，與龍一戰！" << endl;
        cout << "2. 趁龍不注意，悄悄逃走" << endl;
        cout << "選擇：";

        int choice2;
        cin >> choice2;
        while (choice2 != 1 && choice2 != 2) {
            cout << "無效選擇，請輸入 1 或 2：";
            cin >> choice2;
        }

        if (choice2 == 1) {
            if (job == 1 && attack >= 8) {
                cout << "\n════════════════════════════════" << endl;
                cout << "結局：英雄的榮耀" << endl;
                cout << "你揮舞巨劍，" << name << " 戰士的力量震驚了巨龍！" << endl;
                cout << "最終一劍刺穿龍心，龍窟中的寶藏全歸你了！" << endl;
                cout << "你成為了整個王國傳頌的英雄。" << endl;
            } else if (magic >= 9) {
                cout << "\n════════════════════════════════" << endl;
                cout << "隱藏結局：龍與法師的盟約" << endl;
                cout << name << " 法師，你釋放了古老的「龍語術」！" << endl;
                cout << "巨龍竟然停止了攻擊，俯下了牠的頭。" << endl;
                cout << "兩人結成同盟，拯救了即將滅亡的王國。" << endl;
            } else {
                cout << "\n════════════════════════════════" << endl;
                cout << "結局：勇敢的犧牲" << endl;
                cout << name << " 奮力一戰，但面對古老的巨龍，實力差距太大。" << endl;
                cout << "在最後一刻，你的身影化為了守護森林的光芒。" << endl;
            }
        } else {
            if (agility >= 9) {
                cout << "\n════════════════════════════════" << endl;
                cout << "結局：疾風盜賊" << endl;
                cout << name << " 如鬼魅般消失，順帶摸走了一枚古幣。" << endl;
            } else {
                cout << "\n════════════════════════════════" << endl;
                cout << "結局：狼狽逃跑" << endl;
                cout << "龍的火焰燒掉了你半件外套，但你活著跑出了森林。" << endl;
            }
        }
    } else {
        if (job == 3) cout << "\n你的盜賊直覺引導你踏上了小徑，" << endl;
        else          cout << "\n你謹慎地踏上了隱密的小徑，" << endl;
        cout << "發現了一座長滿苔蘚的古老神殿！" << endl;

        cout << "\n神殿入口刻著古代銘文……" << endl;
        cout << "你選擇：" << endl;
        cout << "1. 嘗試解讀銘文並進入神殿" << endl;
        cout << "2. 繼續趕路" << endl;
        cout << "選擇：";

        int choice2;
        cin >> choice2;
        while (choice2 != 1 && choice2 != 2) {
            cout << "無效選擇，請輸入 1 或 2：";
            cin >> choice2;
        }

        if (choice2 == 1) {
            if (job == 2 && magic >= 9) {
                cout << "\n════════════════════════════════" << endl;
                cout << "結局：古代秘術的傳承者" << endl;
                cout << name << " 法師輕易讀出了銘文的意涵。" << endl;
                cout << "你成為三百年來第一位讀懂它的人，獲得了強大的魔法傳承。" << endl;
            } else if (agility >= 9) {
                cout << "\n════════════════════════════════" << endl;
                cout << "結局：盜賊的眼光" << endl;
                cout << "看不懂銘文，但敏銳的直覺讓你迴避所有陷阱，" << endl;
                cout << "帶著一袋古代金幣瀟灑地離開了神殿。" << endl;
            } else {
                cout << "\n════════════════════════════════" << endl;
                cout << "結局：觸發陷阱" << endl;
                cout << "你誤觸了封印陷阱，被傳送到了完全陌生的地方……" << endl;
                cout << "這大概是另一段冒險的開始了。" << endl;
            }
        } else {
            cout << "\n════════════════════════════════" << endl;
            cout << "結局：平淡的旅程" << endl;
            cout << name << " 搖了搖頭，繞過神殿繼續趕路。" << endl;
            cout << "你平安地抵達了目的地。有時候，平凡也是一種幸福。" << endl;
        }
    }

    cout << "\n════════════════════════════════" << endl;
    cout << "感謝遊玩！" << endl;

    return 0;
}
