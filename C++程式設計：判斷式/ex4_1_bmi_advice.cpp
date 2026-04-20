#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string name;
    double weight, height;

    cout << "=== BMI 健康評估系統 ===" << endl;
    cout << "姓名：";     cin >> name;
    cout << "體重(kg)："; cin >> weight;
    cout << "身高(cm)："; cin >> height;

    if (weight <= 0 || height <= 0) {
        cout << "錯誤：體重和身高必須為正數！" << endl;
        return 1;
    }

    double h = height / 100.0;
    double bmi = weight / (h * h);

    string category, advice;

    if (bmi < 18.5) {
        category = "體重過輕";
        advice   = "建議增加營養攝取，適當重訓增加肌肉量。";
    } else if (bmi < 24.0) {
        category = "正常範圍";
        advice   = "體重維持得很好！繼續保持健康的生活習慣。";
    } else if (bmi < 27.0) {
        category = "體重過重";
        advice   = "建議控制飲食，增加有氧運動頻率。";
    } else if (bmi < 30.0) {
        category = "輕度肥胖";
        advice   = "建議尋求營養師協助，制訂減重計畫。";
    } else {
        category = "中重度肥胖";
        advice   = "建議就醫評估，在醫師指導下進行健康管理。";
    }

    cout << fixed << setprecision(1);
    cout << "\n" << name << " 的評估結果：" << endl;
    cout << "BMI：" << bmi << endl;
    cout << "分類：" << category << endl;
    cout << "建議：" << advice << endl;

    return 0;
}
