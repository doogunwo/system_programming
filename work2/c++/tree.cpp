/*

학생 수를 입력받은 다음, 학생의 이름, 중간, 기말 점수를 기록하는 구조체를
학생 수만큼 동적으로 할당받아서, 이를 트리 구조체로 활용하여 트리 탐색을 할 수 있는 프로그램을 작성하시오.

이 문제를 c++ 의 STL의 map 컨테이너를 사용해서 해결하시오

*/

#include <iostream>
#include <map>
#include <string>

using namespace std;
struct record {
    string name;
    int mid;
    int final;
};



int main(){
    int num;
    cout << "Enter the num:";
    cin >> num;

    map<string, record> recordMap;

    for(int i = 0 ; i< num; i++){
        record record;

        cout << "Enter record name: ";
        cin >> record.name;

        cout << "Enter record mid: ";
        cin >> record.mid;

        cout << "Enter recrod final: ";
        cin >> record.final;

        recordMap[record.name] = record;
    }
    
    string search_name;
    cout << "Enter record'name to search:";
    cin >> search_name;

    if(recordMap.find(search_name) != recordMap.end()) {
        
        cout << "Name: " << recordMap[search_name].name << endl;
        cout << "mid : " << recordMap[search_name].mid << endl;
        cout << "final:" << recordMap[search_name].final << endl;
    }

    return 0;
}   