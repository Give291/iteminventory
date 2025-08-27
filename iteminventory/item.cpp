#include <iostream>  // ����� (cout, endl)
#include <string>    // ���ڿ�(string Ŭ����)
using namespace std;

// =============================
// ���ÿ� ������ Ŭ����
// =============================
class Item {
protected:
    string name_;   // ������ �̸� (std::string: ���� �迭���� ���� ���ؼ� ���)
    int price_;     // ������ ���� (�����ϱ� int ���)
public:
    // ������: ������ ���� �� �̸��� ������ �ʱ�ȭ�Ѵ�.
    // �⺻���� �����߱� ������ �ƹ� �� �� ������ "�̸�����", 0 ���� ������
    Item(const string& name = "�̸�����", int price = 0)
        : name_(name), price_(price) {
    }

    // ������ ���� ��� (�̸�, ����)
    void PrintInfo() const {
        cout << "[�̸�: " << name_ << ", ����: " << price_ << "G]" << endl;
    }
};

// =============================
// ���ø� �κ��丮 Ŭ����
// =============================
// template <typename T> �� �ڷ����� �ܺο��� ���� �� �ֵ��� �����.
// ��: Inventory<Item>, Inventory<Weapon> �� � Ÿ���̵� ����
template <typename T>
class Inventory {
private:
    T* pItems_;      // ���� �迭 (new�� �� �޸𸮿� �Ҵ� �� �κ��丮 ������ ����)
    int capacity_;   // �κ��丮�� �ִ� �뷮
    int size_;       // ���� ����ִ� ������ ����
public:
    // -----------------------------
    // ������
    // -----------------------------
    Inventory(int capacity = 10)   // �⺻ �뷮�� 10
        : pItems_(nullptr), capacity_(capacity), size_(0)
    {
        if (capacity_ <= 0) capacity_ = 1; // ������: 0 ���� ������ �ּ� 1�� ����
        pItems_ = new T[capacity_];        // ���� �迭 ���� �Ҵ� (T Ÿ���� ��ü �迭)
    }

    // -----------------------------
    // �Ҹ���
    // -----------------------------
    ~Inventory() {
        delete[] pItems_;   // new�� �Ҵ��� �迭�� �ݵ�� delete[] �� �����ؾ� ��
        pItems_ = nullptr;  // �����ϰ� nullptr�� �ʱ�ȭ (dangling pointer ����)
    }

    // -----------------------------
    // ������ �߰�
    // -----------------------------
    void AddItem(const T& item) {
        // ���� ������ ���������� �� �迭�� ����ְ� size_ ����
        if (size_ < capacity_) {
            pItems_[size_++] = item;
            // ���⼭ ���� �����ڴ� T Ŭ������ ���� �����ڸ� ��� (���� ����)
        }
        else {
            cout << "�κ��丮�� �� á���ϴ�!" << endl;
        }
    }

    // -----------------------------
    // ������ ������ ����
    // -----------------------------
    void RemoveLastItem() {
        if (size_ > 0) {
            size_--;  // ���� �޸𸮸� ����� �� �ƴϰ�, ������ �� ���� size�� ����
        }
        else {
            cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
        }
    }

    // -----------------------------
    // ���� ����ִ� ������ ���� ��ȯ
    // -----------------------------
    int GetSize() const { return size_; }

    // -----------------------------
    // �κ��丮 �ִ� �뷮 ��ȯ
    // -----------------------------
    int GetCapacity() const { return capacity_; }

    // -----------------------------
    // ��� ������ ���
    // -----------------------------
    void PrintAllItems() const {
        if (size_ == 0) { // ����� ���
            cout << "(�������)" << endl;
            return;
        }
        for (int i = 0; i < size_; i++) {
            // �� �������� PrintInfo() ȣ��
            // ���⼭ �߿��� ��: T Ÿ�Կ� �ݵ�� PrintInfo() �Լ��� �־�� ��
            pItems_[i].PrintInfo();
        }
    }
};

// =============================
// ��� ���� (main �Լ�)
// =============================
int main() {
    // Item Ÿ���� ���� �� �ִ� �κ��丮 ���� (�ִ� 3ĭ)
    Inventory<Item> inv(3);

    // AddItem ȣ�� �� ���� �迭�� ���ʴ�� �����
    inv.AddItem(Item("ö��", 100));
    inv.AddItem(Item("ȸ����", 50));
    inv.AddItem(Item("����", 80));

    cout << "=== �κ��丮 ��� ===" << endl;
    inv.PrintAllItems();   // ���ݱ��� �� ������ �� ���

    cout << "������ ������ ����" << endl;
    inv.RemoveLastItem();  // ���� ���ŵ�
    inv.PrintAllItems();   // ���� ������ ���

    return 0; // main ����Ǹ鼭 inv �Ҹ��� �ڵ� ȣ�� �� �޸� ����
}
