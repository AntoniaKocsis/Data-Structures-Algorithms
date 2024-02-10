#include <iostream>
using namespace std;

int main() {
    pair<int,int>* arr = new pair<int,int>[10];
    arr[0] = make_pair(2,3);
    cout<<arr[0].first<<" "<<arr[0].second;
    return 0;
}
