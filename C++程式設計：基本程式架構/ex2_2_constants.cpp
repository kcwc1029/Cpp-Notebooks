#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double PI = 3.14159265358979;
    const int RADIUS = 5;

    double area = PI * RADIUS * RADIUS;
    double circumference = 2 * PI * RADIUS;

    cout << "半徑：" << RADIUS << endl;
    cout << "面積：" << area << endl;
    cout << "圓周長：" << circumference << endl;

    return 0;
}
