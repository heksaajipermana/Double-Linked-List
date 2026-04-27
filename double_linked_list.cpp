/*
    Double Linked List Implementation in C++

    Features:
    - Insert (first, last, after)
    - Delete (first, last, after)
    - Search
    - Count node
    - Reverse list

    Notes:
    - Menggunakan pointer (non-OOP)
    - Aman untuk operasi dasar linked list

    Author: Heksa Aji Permana
*/
#include <iostream>
using namespace std;

typedef struct node *address;

struct node {
    int data;
    address next;
    address prev;
};

address first = NULL;
address last = NULL;

address allocate_data(int value){
    address temp = new node;
    temp->data = value;
    temp->next = temp->prev = NULL;
    return temp;
}

address search(int value){
    address temp = first;
    while(temp != NULL && temp->data != value){
        temp = temp->next;
    }
    return temp;
}

void insert_first(address latest){
    if(first == NULL){
        first = last = latest;
    } else {
        latest->next = first;
        first->prev = latest;
        first = latest;
    }
}

void insert_last(address latest){
    if(last == NULL){
        first = last = latest;
    } else {
        last->next = latest;
        latest->prev = last;
        last = latest;
    }
}

void insert_after(address exist, address latest){
    if(exist == NULL){
        return;
    }
    if(first == NULL){
        first = last = latest;
    } else {
        if(exist == last){
            exist->next = latest;
            latest->prev = exist;
            last = latest;
        } else {
            latest->next = exist->next;
            latest->prev = exist;
            exist->next->prev = latest;
            exist->next = latest;
        }
    }
}

void delete_first(){
    if(first == NULL){
        return;
    } else if(first == last){
        delete first;
        first = last = NULL;
    } else {
        first = first->next;
        delete first->prev;
        first->prev = NULL;
    }
}

void delete_last(){
    if(last == NULL){
        return;
    } else if(last == first){
        delete last;
        last = first = NULL;
    } else {
        last = last->prev;
        delete last->next;
        last->next = NULL;
    }
}

void delete_after(address exist){
    if(exist == NULL || exist->next == NULL){
        return;
    } else if(exist == last->prev){
        delete exist->next;
        exist->next = NULL;
        last = exist;
    } else {
        exist->next = exist->next->next;
        delete exist->next->prev;
        exist->next->prev = exist;
    }
}

void print(){
    if(first == NULL){
        cout << "List masih kosong\n";
        return;
    }
    address temp = first;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int count_node(){
    address temp = first;
    int total = 0;
    while(temp != NULL){
        total++;
        temp = temp->next;
    }
    return total;
}

void reverse(){
    if(first == NULL){
        return;
    }
    address temp = NULL;
    address current = first;
    while(current != NULL){
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    temp = first;
    first = last;
    last = temp;
}

int main(){
    cout << "=== DEMO DOUBLY LINKED LIST ===\n";

    // ================= INSERT =================
    insert_first(allocate_data(10)); // 10
    insert_first(allocate_data(5));  // 5 10
    insert_last(allocate_data(20));  // 5 10 20
    insert_last(allocate_data(30));  // 5 10 20 30

    cout << "Setelah insert:\n";
    print();

    // ================= SEARCH =================
    address node10 = search(10);
    if(node10 != NULL){
        cout << "Data 10 ditemukan\n";
    }

    // ================= INSERT AFTER =================
    insert_after(node10, allocate_data(15)); // setelah 10

    cout << "Setelah insert 15 setelah 10:\n";
    print();

    // ================= DELETE FIRST =================
    delete_first();

    cout << "Setelah delete first:\n";
    print();

    // ================= DELETE LAST =================
    delete_last();

    cout << "Setelah delete last:\n";
    print();

    // ================= DELETE AFTER =================
    address node15 = search(15);
    delete_after(node15); // hapus setelah 15

    cout << "Setelah delete setelah 15:\n";
    print();

    // ================= COUNT =================
    cout << "Jumlah node: " << count_node() << endl;

    // ================= REVERSE =================
    reverse();

    cout << "Setelah reverse:\n";
    print();
    return 0;
}