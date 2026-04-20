#include <iostream>
using namespace std;

int main() {
    int age;
    double gpa;
    char ans;

    cout << "=== 研究所錄取資格審查 ===" << endl;
    cout << "年齡：";             cin >> age;
    cout << "GPA：";              cin >> gpa;
    cout << "有推薦信？(y/n)：";  cin >> ans;
    bool hasRecommendation = (ans == 'y' || ans == 'Y');

    bool ageOK = (age >= 22 && age <= 35);
    bool gpaOK = (gpa > 3.0);

    if (gpaOK && (ageOK || hasRecommendation)) {
        cout << "\n✅ 恭喜！符合申請資格。" << endl;
    } else {
        cout << "\n❌ 抱歉，目前不符合資格。" << endl;
        if (!gpaOK) {
            cout << "  → GPA 需在 3.0 以上（目前 " << gpa << "）" << endl;
        }
        if (!ageOK && !hasRecommendation) {
            cout << "  → 需符合年齡條件（22-35）或具備推薦信" << endl;
        }
    }

    return 0;
}
