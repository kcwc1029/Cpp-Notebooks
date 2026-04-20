#include <iostream>
using namespace std;

int main() {
    int length, width;

    cout << "請輸入矩形的長和寬（空格分隔）：";
    cin >> length >> width;

    int area = length * width;
    int perimeter = 2 * (length + width);

    cout << "面積 = " << area << endl;
    cout << "周長 = " << perimeter << endl;

    return 0;
}
