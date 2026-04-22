#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string name;
    double weight, height;

    cout << "=== BMI 計算機 ===" << endl;
    cout << "請輸入姓名：";
    cin >> name;
    cout << "請輸入體重（公斤）：";
    cin >> weight;
    cout << "請輸入身高（公分）：";
    cin >> height;

    double heightM = height / 100.0;
    double bmi = weight / (heightM * heightM);

    string category;
    if      (bmi < 18.5) category = "體重過輕";
    else if (bmi < 24.0) category = "正常範圍";
    else if (bmi < 27.0) category = "體重過重";
    else if (bmi < 30.0) category = "輕度肥胖";
    else if (bmi < 35.0) category = "中度肥胖";
    else                 category = "重度肥胖";

    cout << fixed << setprecision(2);
    cout << "\n" << name << " 的 BMI = " << bmi << endl;
    cout << "健康狀態：" << category << endl;

    return 0;
}
