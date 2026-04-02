#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct SongNode {
    int songId;
    string songName;
    string artistName;
    int duration;
    int playCount;
    SongNode* next;
    SongNode* prev;

    SongNode(int id, const string& sName, const string& aName, int dur)
        : songId(id), songName(sName), artistName(aName), duration(dur),
          playCount(0), next(nullptr), prev(nullptr) {}
};

SongNode* head = nullptr;
SongNode* tail = nullptr;
SongNode* currentSong = nullptr;
int playlistSize = 0;

SongNode* findSong(int songId) {
    if (head == nullptr) return nullptr;

    SongNode* temp = head;
    do {
        if (temp->songId == songId) return temp;
        temp = temp->next;
    } while (temp != head);

    return nullptr;
}

SongNode* getNodeAtPosition(int pos) {
    if (pos < 1 || pos > playlistSize || head == nullptr) return nullptr;

    SongNode* temp = head;
    for (int i = 1; i < pos; i++) {
        temp = temp->next;
    }
    return temp;
}

void addSong(int songId, const string& songName, const string& artistName, int duration) {
    if (findSong(songId) != nullptr) {
        cout << "Song already exists." << '\n';
        return;
    }

    SongNode* newNode = new SongNode(songId, songName, artistName, duration);

    if (head == nullptr) {
        head = tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
        tail = newNode;
    }

    playlistSize++;
    cout << "Song added." << '\n';
}

void removeSong(int songId) {
    if (head == nullptr) {
        cout << "Playlist is empty." << '\n';
        return;
    }

    SongNode* target = findSong(songId);
    if (target == nullptr) {
        cout << "Not found." << '\n';
        return;
    }

    if (playlistSize == 1) {
        delete target;
        head = tail = currentSong = nullptr;
        playlistSize = 0;
        cout << "Song removed." << '\n';
        return;
    }

    SongNode* nextNode = target->next;

    target->prev->next = target->next;
    target->next->prev = target->prev;

    if (target == head) head = target->next;
    if (target == tail) tail = target->prev;

    if (currentSong == target) {
        currentSong = nextNode;
    }

    delete target;
    playlistSize--;

    head->prev = tail;
    tail->next = head;

    cout << "Song removed." << '\n';
}

void playSong(int songId) {
    if (head == nullptr) {
        cout << "Playlist is empty." << '\n';
        return;
    }

    SongNode* target = findSong(songId);
    if (target == nullptr) {
        cout << "Not found." << '\n';
        return;
    }

    currentSong = target;
    currentSong->playCount++;
    cout << "Playing: " << currentSong->songName << '\n';
}

void nextSong() {
    if (currentSong == nullptr) {
        cout << "No song is currently playing." << '\n';
        return;
    }

    currentSong = currentSong->next;
    currentSong->playCount++;
    cout << "Playing: " << currentSong->songName << '\n';
}

void prevSong() {
    if (currentSong == nullptr) {
        cout << "No song is currently playing." << '\n';
        return;
    }

    currentSong = currentSong->prev;
    currentSong->playCount++;
    cout << "Playing: " << currentSong->songName << '\n';
}

void moveAfter(int A, int B) {
    SongNode* nodeA = findSong(A);
    SongNode* nodeB = findSong(B);

    if (nodeA == nullptr || nodeB == nullptr) {
        cout << "Not found." << '\n';
        return;
    }

    if (playlistSize < 2 || A == B || nodeB->next == nodeA) {
        cout << "Move ignored." << '\n';
        return;
    }

    if (playlistSize > 1) {
        nodeA->prev->next = nodeA->next;
        nodeA->next->prev = nodeA->prev;

        if (nodeA == head) head = nodeA->next;
        if (nodeA == tail) tail = nodeA->prev;
    }

    SongNode* afterB = nodeB->next;

    nodeA->next = afterB;
    nodeA->prev = nodeB;
    nodeB->next = nodeA;
    afterB->prev = nodeA;

    if (nodeB == tail) tail = nodeA;

    head->prev = tail;
    tail->next = head;

    cout << "Song moved." << '\n';
}

void reverseSegment(int L, int R) {
    if (L < 1 || R > playlistSize || L >= R) {
        cout << "Invalid range." << '\n';
        return;
    }

    SongNode* leftNode = getNodeAtPosition(L);
    SongNode* rightNode = getNodeAtPosition(R);

    SongNode* beforeLeft = leftNode->prev;
    SongNode* afterRight = rightNode->next;

    SongNode* curr = leftNode;
    while (curr != afterRight) {
        SongNode* tempNext = curr->next;
        curr->next = curr->prev;
        curr->prev = tempNext;
        curr = tempNext;
    }

    if (L == 1 && R == playlistSize) {
        head = rightNode;
        tail = leftNode;
        head->prev = tail;
        tail->next = head;
    } else {
        beforeLeft->next = rightNode;
        rightNode->prev = beforeLeft;

        leftNode->next = afterRight;
        afterRight->prev = leftNode;

        if (L == 1) head = rightNode;
        if (R == playlistSize) tail = leftNode;

        head->prev = tail;
        tail->next = head;
    }

    cout << "Segment reversed." << '\n';
}

void jumpK(int K) {
    if (K < 0) {
        cout << "Invalid jump." << '\n';
        return;
    }

    if (currentSong == nullptr) {
        cout << "No song is currently playing." << '\n';
        return;
    }

    for (int i = 0; i < K; i++) {
        currentSong = currentSong->next;
    }

    currentSong->playCount++;
    cout << "Playing: " << currentSong->songName << '\n';
}

void printPlaylist() {
    cout << "Playlist:";
    if (head != nullptr) {
        SongNode* temp = head;
        do {
            cout << " " << temp->songName;
            temp = temp->next;
        } while (temp != head);
    }
    cout << '\n';

    if (currentSong == nullptr) {
        cout << "Current: None" << '\n';
    } else {
        cout << "Current: " << currentSong->songName << '\n';
    }
}

void clearPlaylist() {

    if (head == nullptr) return;

    SongNode* curr = head->next;

    while (curr != head) {
        SongNode* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }

    delete head;

    head = tail = currentSong = nullptr;
    playlistSize = 0;
}

int main() {
    string command;

    while (cin >> command) {
        if (command == "ADD") {
            int songId, duration;
            string songName, artistName;
            cin >> songId >> songName >> artistName >> duration;
            addSong(songId, songName, artistName, duration);
        }
        else if (command == "REMOVE") {
            int songId;
            cin >> songId;
            removeSong(songId);
        }
        else if (command == "PLAY") {
            int songId;
            cin >> songId;
            playSong(songId);
        }
        else if (command == "NEXT") {
            nextSong();
        }
        else if (command == "PREV") {
            prevSong();
        }
        else if (command == "MOVE_AFTER") {
            int A, B;
            cin >> A >> B;
            moveAfter(A, B);
        }
        else if (command == "REVERSE_SEGMENT") {
            int L, R;
            cin >> L >> R;
            reverseSegment(L, R);
        }
        else if (command == "JUMP") {
            int K;
            cin >> K;
            jumpK(K);
        }
        else if (command == "PRINT") {
            printPlaylist();
        }
        else if (command == "EXIT") {
            cout << "Exiting. Goodbye!" << '\n';
            clearPlaylist();
            break;
        }
        else {
            cout << "Invalid command." << '\n';
        }
    }

    return 0;
}
