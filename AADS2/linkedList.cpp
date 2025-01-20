#include <iostream>
#include <ctime>
#include <random>
#include <limits.h>
#include <cstdlib>

#define APPEND_MENU 1
#define DELETE_MENU 2
#define REMOVEMINMAX_MENU 3
#define EXIT_MENU -1

using std::cin;
using std::cout;
using std::endl;

struct ListNode {
    int num;
    ListNode* next;
    ListNode* prev;

    ListNode(int nval) : num(nval), next(nullptr), prev(nullptr) {}
};

void initList(ListNode*& listHead);

void append(ListNode*& listHead, int value);

void remove(ListNode*& listHead, int value);

void display(ListNode* listHead);

void freeList(ListNode* listHead);

void removeMinMax(ListNode* listHead, ListNode*& listResultHead);

int main() {
    ListNode* listHead = nullptr;
    ListNode* listResultHead = nullptr;
    initList(listHead);

    while (true) {
    int menuItem{}, inputElem{};
    cout << "Current List: "; display(listHead);
    cout << "MENU" << endl;
    cout << "1. Append a number" << endl;
    cout << "2. Delete a number" << endl; 
    cout << "3. Remove 2 Min and 2 Max" << endl;
    cout << "Exit: Enter -1 to exit the program" << endl;
    cout << "Enter the menu item: ";
    cin >> menuItem;
        switch (menuItem) {
            case APPEND_MENU:
                cout << "Enter an integer to append: ";
                cin >> inputElem;
                append(listHead, inputElem);
                break;
            case DELETE_MENU:
                cout << "Enter an integer to delete: ";
                cin >> inputElem;
                remove(listHead, inputElem);
                break;
            case REMOVEMINMAX_MENU:
                removeMinMax(listHead, listResultHead);
                cout << "Result List: "; display(listResultHead);
                return 0;
            case EXIT_MENU:
                return 0;
            default:
                cout << "Not the MENU item!" << endl;;
                break;
        }
    }
    freeList(listHead);
    freeList(listResultHead);
    return 0;
}

void initList(ListNode*& listHead) {
    std::mt19937 rnd;
    rnd.seed(std::time(nullptr));
    int rndsize = abs(static_cast<int>(rnd())) % 11 + 5;
    cout << "List size: " << rndsize << endl;
    for (int i = 0; i < rndsize; i++)
        append(listHead, rnd() % 200 - 100);
}

void append(ListNode*& listHead, int value) {
    ListNode* resultNodePtr = new ListNode(value);
    if (listHead == nullptr) {
        listHead = resultNodePtr;
    } else {
        ListNode* anotherNodePtr = listHead;
        while (anotherNodePtr->next != nullptr)
            anotherNodePtr = anotherNodePtr->next;
        anotherNodePtr->next = resultNodePtr;
        resultNodePtr->prev = anotherNodePtr;
    }
}

void remove(ListNode*& listHead, int value) {
    if (listHead != nullptr) {
        bool Found{true};
        ListNode* anotherNodePtr = listHead;
        while (anotherNodePtr->num != value && 
        (Found = (anotherNodePtr->next != nullptr)))
            anotherNodePtr = anotherNodePtr->next;
        if (Found) {
            if (anotherNodePtr == listHead) {
                listHead = anotherNodePtr->next;
            }
            if (anotherNodePtr->prev != nullptr)
                anotherNodePtr->prev->next = anotherNodePtr->next;
            if (anotherNodePtr->next != nullptr)
                anotherNodePtr->next->prev = anotherNodePtr->prev;
            delete anotherNodePtr;
        }
        else {
            cout << "Entered value is not in the list!" << endl;
        }
    }
    else
        cout << "List is empty. Can't remove." << endl;
}

void display(ListNode* listHead) {
    ListNode* anotherNodePtr = listHead;
    while (anotherNodePtr != nullptr) {
        cout << anotherNodePtr->num << ' ';
        anotherNodePtr = anotherNodePtr->next;
    }
    cout << endl;
}

void freeList(ListNode* listHead) {
    ListNode* tempNodePtr;
    while (listHead) {
        tempNodePtr = listHead;
        listHead = listHead->next;
        delete tempNodePtr;
    }
}

void removeMinMax(ListNode* listHead, ListNode*& listResultHead) {
    if (!listHead) return;
    
    ListNode* checkNodePtr = listHead;
    int sizeList{};
    while (checkNodePtr != nullptr) {
        sizeList++;
        checkNodePtr = checkNodePtr->next;
    }

    int mn = INT_MAX, mnprev = INT_MAX;
    int mx = INT_MIN, mxprev = INT_MIN;

    ListNode* anotherNodePtr = listHead;
    while (anotherNodePtr != nullptr) {
        if (anotherNodePtr->num < mn) {
            mnprev = mn;
            mn = anotherNodePtr->num;
        } else if (anotherNodePtr->num < mnprev 
        && anotherNodePtr->num != mn) {
            mnprev = anotherNodePtr->num;
        }

        if (anotherNodePtr->num > mx) {
            mxprev = mx;
            mx = anotherNodePtr->num;
        } else if (anotherNodePtr->num > mxprev 
        && anotherNodePtr->num != mx) {
            mxprev = anotherNodePtr->num;
        }

        anotherNodePtr = anotherNodePtr->next;
    }

    ListNode* resultNodePtr = listHead;
    while (resultNodePtr != nullptr) {
        if ((resultNodePtr->num != mn)
        && (resultNodePtr->num != mnprev)
        && (resultNodePtr->num != mx)
        && (resultNodePtr->num != mxprev))
            append(listResultHead, resultNodePtr->num);
        resultNodePtr = resultNodePtr->next;
    }
} 
