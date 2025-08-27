#include <iostream>  // 입출력 (cout, endl)
#include <string>    // 문자열(string 클래스)
using namespace std;

// =============================
// 예시용 아이템 클래스
// =============================
class Item {
protected:
    string name_;   // 아이템 이름 (std::string: 문자 배열보다 쓰기 편리해서 사용)
    int price_;     // 아이템 가격 (정수니까 int 사용)
public:
    // 생성자: 아이템 만들 때 이름과 가격을 초기화한다.
    // 기본값도 지정했기 때문에 아무 값 안 넣으면 "이름없음", 0 으로 생성됨
    Item(const string& name = "이름없음", int price = 0)
        : name_(name), price_(price) {
    }

    // 아이템 정보 출력 (이름, 가격)
    void PrintInfo() const {
        cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
    }
};

// =============================
// 템플릿 인벤토리 클래스
// =============================
// template <typename T> → 자료형을 외부에서 정할 수 있도록 만든다.
// 예: Inventory<Item>, Inventory<Weapon> 등 어떤 타입이든 가능
template <typename T>
class Inventory {
private:
    T* pItems_;      // 동적 배열 (new로 힙 메모리에 할당 → 인벤토리 아이템 저장)
    int capacity_;   // 인벤토리의 최대 용량
    int size_;       // 현재 들어있는 아이템 개수
public:
    // -----------------------------
    // 생성자
    // -----------------------------
    Inventory(int capacity = 10)   // 기본 용량은 10
        : pItems_(nullptr), capacity_(capacity), size_(0)
    {
        if (capacity_ <= 0) capacity_ = 1; // 안정성: 0 이하 들어오면 최소 1로 보정
        pItems_ = new T[capacity_];        // 실제 배열 공간 할당 (T 타입의 객체 배열)
    }

    // -----------------------------
    // 소멸자
    // -----------------------------
    ~Inventory() {
        delete[] pItems_;   // new로 할당한 배열은 반드시 delete[] 로 해제해야 함
        pItems_ = nullptr;  // 안전하게 nullptr로 초기화 (dangling pointer 방지)
    }

    // -----------------------------
    // 아이템 추가
    // -----------------------------
    void AddItem(const T& item) {
        // 아직 공간이 남아있으면 → 배열에 집어넣고 size_ 증가
        if (size_ < capacity_) {
            pItems_[size_++] = item;
            // 여기서 대입 연산자는 T 클래스의 복사 생성자를 사용 (깊은 복사)
        }
        else {
            cout << "인벤토리가 꽉 찼습니다!" << endl;
        }
    }

    // -----------------------------
    // 마지막 아이템 제거
    // -----------------------------
    void RemoveLastItem() {
        if (size_ > 0) {
            size_--;  // 실제 메모리를 지우는 건 아니고, 접근할 수 없게 size만 줄임
        }
        else {
            cout << "인벤토리가 비어있습니다." << endl;
        }
    }

    // -----------------------------
    // 현재 들어있는 아이템 개수 반환
    // -----------------------------
    int GetSize() const { return size_; }

    // -----------------------------
    // 인벤토리 최대 용량 반환
    // -----------------------------
    int GetCapacity() const { return capacity_; }

    // -----------------------------
    // 모든 아이템 출력
    // -----------------------------
    void PrintAllItems() const {
        if (size_ == 0) { // 비었을 경우
            cout << "(비어있음)" << endl;
            return;
        }
        for (int i = 0; i < size_; i++) {
            // 각 아이템의 PrintInfo() 호출
            // 여기서 중요한 점: T 타입에 반드시 PrintInfo() 함수가 있어야 함
            pItems_[i].PrintInfo();
        }
    }
};

// =============================
// 사용 예시 (main 함수)
// =============================
int main() {
    // Item 타입을 담을 수 있는 인벤토리 생성 (최대 3칸)
    Inventory<Item> inv(3);

    // AddItem 호출 → 내부 배열에 차례대로 저장됨
    inv.AddItem(Item("철검", 100));
    inv.AddItem(Item("회복약", 50));
    inv.AddItem(Item("방패", 80));

    cout << "=== 인벤토리 목록 ===" << endl;
    inv.PrintAllItems();   // 지금까지 들어간 아이템 다 출력

    cout << "마지막 아이템 제거" << endl;
    inv.RemoveLastItem();  // 방패 제거됨
    inv.PrintAllItems();   // 남은 아이템 출력

    return 0; // main 종료되면서 inv 소멸자 자동 호출 → 메모리 해제
}
