#include <iostream>
#include <string>
using namespace std;

// 模擬大型資料結構（約 400+ bytes）
struct BigData {
    int   nums[100];
    string label;
    double value;
};

// 傳值：建立整個結構體的副本（代價高！）
void process_by_value(BigData bd) {
    bd.value *= 2;    // 只修改副本
    cout << "  [傳值]       value 副本 = " << bd.value << endl;
}

// 傳 const 參考：不複製，只讀（推薦用於唯讀操作）
void process_by_cref(const BigData& bd) {
    cout << "  [const 參考] label = " << bd.label
         << "，value = " << bd.value << endl;
    // bd.value = 0;   // ❌ 編譯錯誤
}

// 傳參考：不複製，可修改（需要修改時使用）
void process_by_ref(BigData& bd, double newValue) {
    bd.value = newValue;    // 修改原始資料
    cout << "  [參考]       value 已更新為 " << bd.value << endl;
}

int main() {
    BigData data;
    data.label = "測試資料";
    data.value = 3.14;
    for (int i = 0; i < 100; i++) data.nums[i] = i;

    cout << "=== 三種傳遞方式的效果 ===" << endl;
    cout << "原始 value = " << data.value << endl;

    process_by_value(data);
    cout << "傳值後  value = " << data.value << "（沒有改變）" << endl;

    process_by_ref(data, 99.9);
    cout << "傳參考後 value = " << data.value << "（已改變）" << endl;

    process_by_cref(data);

    cout << "\n=== 三種傳遞方式的選擇指南 ===" << endl;
    cout << "┌─────────────────────────┬──────────────────────────────┐" << endl;
    cout << "│ 情況                    │ 建議傳遞方式                 │" << endl;
    cout << "├─────────────────────────┼──────────────────────────────┤" << endl;
    cout << "│ 小型資料，不修改        │ 傳值（int, double, char）    │" << endl;
    cout << "│ 大型資料，不修改        │ const 參考（string, struct） │" << endl;
    cout << "│ 需要修改呼叫者的資料    │ 參考                         │" << endl;
    cout << "│ 需要同時回傳多個值      │ 參考作為輸出參數             │" << endl;
    cout << "└─────────────────────────┴──────────────────────────────┘" << endl;

    return 0;
}
