#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Song {
    string title;
    string artist;
    Song* prev;
    Song* next;
};
Song* headPtr    = nullptr;
Song* tailPtr    = nullptr;
Song* currentPtr = nullptr;
Song* createSong(const string& title, const string& artist) {
    Song* newSong = new Song;
    newSong->title  = title;
    newSong->artist = artist;
    newSong->prev   = nullptr;
    newSong->next   = nullptr;
    return newSong;
}
void addSong(const string& title, const string& artist) {
    Song* newSong = createSong(title, artist);

    if (headPtr == nullptr) { 
        headPtr = tailPtr = currentPtr = newSong;
    } else {
        tailPtr->next = newSong;
        newSong->prev = tailPtr;
        tailPtr = newSong;
    }
    cout << "Song \"" << title << "\" by " << artist << " added to playlist.\n";
}
void deleteSong(const string& title) {
    if (headPtr == nullptr) {
        cout << "Playlist is empty. Nothing to delete.\n";
        return;
    }

    Song* temp = headPtr;
    while (temp != nullptr && temp->title != title) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Song with title \"" << title << "\" not found in playlist.\n";
        return;
    }
    if (temp == currentPtr) {
        if (currentPtr->next != nullptr)
            currentPtr = currentPtr->next;
        else if (currentPtr->prev != nullptr)
            currentPtr = currentPtr->prev;
        else
            currentPtr = nullptr;
    }
    if (temp == headPtr) {
        headPtr = headPtr->next;
        if (headPtr != nullptr)
            headPtr->prev = nullptr;
    }
    else if (temp == tailPtr) {
        tailPtr = tailPtr->prev;
        if (tailPtr != nullptr)
            tailPtr->next = nullptr;
    }
    else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    cout << "Song \"" << temp->title << "\" deleted from playlist.\n";
    delete temp;

    if (headPtr == nullptr) {
        tailPtr = nullptr;
        currentPtr = nullptr;
    }
}
void playNext() {
    if (currentPtr == nullptr) {
        cout << "Playlist is empty.\n";
    } else if (currentPtr->next == nullptr) {
        cout << "You are at the last song. Cannot go to next.\n";
    } else {
        currentPtr = currentPtr->next;
        cout << "Now playing: " << currentPtr->title
             << " by " << currentPtr->artist << endl;
    }
}
void playPrevious() {
    if (currentPtr == nullptr) {
        cout << "Playlist is empty.\n";
    } else if (currentPtr->prev == nullptr) {
        cout << "You are at the first song. Cannot go to previous.\n";
    } else {
        currentPtr = currentPtr->prev;
        cout << "Now playing: " << currentPtr->title
             << " by " << currentPtr->artist << endl;
    }
}
void showCurrentSong() {
    if (currentPtr == nullptr) {
        cout << "No song is currently selected.\n";
    } else {
        cout << "Currently playing: " << currentPtr->title
             << " by " << currentPtr->artist << endl;
    }
}
void displayPlaylist() {
    if (headPtr == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }
    cout << "\n--- Playlist ---\n";
    Song* temp = headPtr;
    int index = 1;
    while (temp != nullptr) {
        cout << index << ". " << temp->title << " by " << temp->artist;
        if (temp == currentPtr) cout << "  <-- Now Playing";
        cout << endl;
        temp = temp->next;
        index++;
    }
    cout << "----------------\n";
}
void freePlaylist() {
    Song* temp = headPtr;
    while (temp != nullptr) {
        Song* nextSong = temp->next;
        delete temp;
        temp = nextSong;
    }
    headPtr = tailPtr = currentPtr = nullptr;
}
int main() {
    int choice;
    string title, artist;
    do {
        cout << "\n===== MUSIC PLAYLIST MANAGER =====\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song by Title\n";
        cout << "3. Show Current Song\n";
        cout << "4. Play Next Song\n";
        cout << "5. Play Previous Song\n";
        cout << "6. Display Playlist\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a number between 1 and 7.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                addSong(title, artist);
                break;

            case 2:
                cout << "Enter song title to delete: ";
                getline(cin, title);
                deleteSong(title);
                break;

            case 3:
                showCurrentSong();
                break;

            case 4:
                playNext();
                break;

            case 5:
                playPrevious();
                break;
            case 6:
                displayPlaylist();
                break;

            case 7:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Please enter a valid choice (1-7).\n";
        }

    } while (choice != 7);

    freePlaylist();
    return 0;
}