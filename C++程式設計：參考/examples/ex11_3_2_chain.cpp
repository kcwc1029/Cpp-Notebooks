#include <iostream>
#include <string>
using namespace std;

// 簡易字串建構器，示範鏈式呼叫（Method Chaining）
class StringBuilder {
public:
    string data;

    // 每個方法都回傳 *this 的參考，讓下一個方法可以接著呼叫
    StringBuilder& append(const string& s) {
        data += s;
        return *this;    // 回傳自身的參考
    }

    StringBuilder& appendLine(const string& s) {
        data += s + "\n";
        return *this;
    }

    StringBuilder& repeat(const string& s, int times) {
        for (int i = 0; i < times; i++) data += s;
        return *this;
    }

    StringBuilder& clear() {
        data.clear();
        return *this;
    }

    void print() const {
        cout << data;
    }

    int length() const {
        return data.length();
    }
};

// 全域計數器，展示用回傳參考的其他應用
int globalCounter = 0;
int& getCounter() { return globalCounter; }

int main() {
    cout << "=== 鏈式呼叫（Method Chaining）===" << endl;
    StringBuilder sb;

    // 不用鏈式呼叫的寫法（繁瑣）
    // sb.append("C++");
    // sb.append(" 程式設計");
    // sb.appendLine(" 很有趣！");

    // 使用鏈式呼叫（簡潔）
    sb.append("C++")
      .append(" 程式設計")
      .appendLine(" 很有趣！")
      .append("參考（Reference）")
      .appendLine(" 是重要特性。")
      .repeat("★", 10)
      .append("\n");

    sb.print();
    cout << "（共 " << sb.length() << " 個字元）" << endl;

    // cout 也是用鏈式呼叫！
    cout << "\n=== cout 也是鏈式呼叫 ===" << endl;
    cout << "A" << " " << "B" << " " << "C" << endl;
    // 等同於：((cout << "A") << " " << "B") << " " ...
    // 每個 << 都回傳 cout 自身的參考

    cout << "\n=== 全域計數器（透過回傳參考直接操作）===" << endl;
    getCounter() = 10;
    cout << "設定為 10：" << getCounter() << endl;

    ++getCounter();
    cout << "遞增後：" << getCounter() << endl;

    getCounter() += 5;
    cout << "+= 5 後：" << getCounter() << endl;

    return 0;
}
