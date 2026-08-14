//Hotel Booking & Room Management System by Syed Shaheer Ali
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Room {
    int roomNum;
    string roomType;
    double pricePerNight;
    bool isAvailable;
};

struct Booking {
    int bookingID;
    int roomNum;
    int guestID;
    int nights;
    double totalBill;
    string paymentType;
};

struct Guest {
    int guestID;
    string name;
    string cnic;
    string phone;
};

int roomcount = 0;
int bookingcount = 0;
int guestcount = 0;

//Room Management Section
void addRoom(Room rooms[], int &maxRoom) {
    if (maxRoom >= 100) {
        cout << "\nError: Maximum room capacity (100) reached!";
        return;
    }
    cout << "\nEnter Room Number: ";
    cin >> rooms[maxRoom].roomNum;
    cout << "Enter Room Type (Single/Double/Suite): ";
    cin.ignore();
    getline(cin, rooms[maxRoom].roomType);
    cout << "Enter Price Per Night: $";
    cin >> rooms[maxRoom].pricePerNight;
    rooms[maxRoom].isAvailable = true;

    maxRoom++;
    cout << "\nRoom Added Successfully!";
}

void displayAllRooms(Room rooms[], int count) {
    int room_available = 0;
    cout << "\n--- Current Rooms List ---\n";
    for (int i = 0; i < count; i++) {
        cout << "Room No: " << rooms[i].roomNum << " | Type: " << rooms[i].roomType
             << " | Price: $" << rooms[i].pricePerNight << " | Status: "
             << (rooms[i].isAvailable ? "Available" : "Occupied") << endl;

        if (rooms[i].isAvailable) {
            room_available++;
        }
    }
    cout << "\nTotal Rooms Available : " << room_available << endl;
}

void searchRoom(Room rooms[], int count) {
    int roomInput;
    bool found = false;

    cout << "\nEnter Room Number you wish to choose: ";
    cin >> roomInput;
    while (roomInput <= 0) {
        cout << "\nInvalid Room Number. Please try again: ";
        cin >> roomInput;
    }
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNum == roomInput) {
            found = true;
            if (rooms[i].isAvailable) {
                cout << "\nRoom No. " << rooms[i].roomNum << " is Available.";
            }
            else {
                cout << "\nRoom No. " << rooms[i].roomNum << " is Not Available.";
            }
        }
    }
    if (!found) {
        cout << "\nRoom not found.";
    }
}

void updateAvailability(Room rooms[], int &count) {
    int roomInput;
    int choiceInput;

    cout << "\nEnter room no. to change its availability: ";
    cin >> roomInput;
    while (roomInput <= 0) {
        cout << "\nInvalid Room Number. Please try again: ";
        cin >> roomInput;
    }
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNum == roomInput) {
            if (rooms[i].isAvailable) {
                cout << "\nStatus: Room No. " << rooms[i].roomNum << " is Available.";
                cout << "\nPress 1 to set it to occupied(not available), or 0 to exit: ";
                cin >> choiceInput;
                while (choiceInput < 0 || choiceInput > 1 ) {
                    cout << "\nInvalid Input! Press 1 to set it to occupied, or 0 to exit: ";
                    cin >> choiceInput;
                }
                if (choiceInput == 1) {
                    rooms[i].isAvailable = false;
                }
            }
            else {
                cout << "\nStatus: Room No. " << rooms[i].roomNum << " is Not Available.";
                cout << "\nPress 1 to set it to unoccupied(available), or 0 to exit: ";
                cin >> choiceInput;
                while (choiceInput < 0 || choiceInput > 1 ) {
                    cout << "\nInvalid Input! Press 1 to set it to unoccupied, or 0 to exit: ";
                    cin >> choiceInput;
                }
                if (choiceInput == 1) {
                    rooms[i].isAvailable = true;
                }
            }
        }
    }
}

void saveRooms (Room arr[], int &count) {
    ofstream file("rooms.txt");
    if (file.is_open()) {
        file << count << endl;
        for (int i = 0; i < count; i++) {
            file << arr[i].roomNum << endl;
            file << arr[i].roomType << endl;
            file << arr[i].pricePerNight << endl;
            file << arr[i].isAvailable << endl;
        }
        file.close();
        cout << "\nData saved to rooms.txt successfully!";
    }
    else {
        cout << "\nFailed to open file. ";
    }
}

void loadRooms (Room arr[], int &count) {
    ifstream file("rooms.txt");
    if (file.is_open()) {
        if (file >> count) {
            if (count > 100)
                count = 100; // safety bound
            for (int i = 0; i < count; i++) {
                file >> arr[i].roomNum;
                file.ignore(); // clearing newline before getline
                getline(file, arr[i].roomType);
                file >> arr[i].pricePerNight;
                file >> arr[i].isAvailable;
            }
        }
        file.close();
        cout << "\nData loaded from rooms.txt successfully!";
    }
    else {
        cout << "\nrooms.txt not found. It will be created upon saving.";
    }
}

//Guest Management Section
void addGuest(Guest guests[], int &count) {
    if (count >= 100) {
        cout << "\nError: Maximum guest database capacity reached!";
        return;
    }
    cout << "\nEnter your details to proceed:";
    cout << "\nID: ";
    cin >> guests[count].guestID;
    cout << "\nName: ";
    cin.ignore();
    getline(cin, guests[count].name);
    cout << "\nCNIC: ";
    cin >> guests[count].cnic;
    cout << "\nPhone: ";
    cin >> guests[count].phone;
    count++;
}

void findGuest(Guest guests[], int count) {
    int searchID;
    bool guestFound = false;
    cout << "\nEnter ID to search for guest: ";
    cin >> searchID;
    for (int i = 0; i < count; i++) {
        if (guests[i].guestID == searchID) {
            guestFound = true;
            cout << "\nGuest Found!\n";
            cout << guests[i].guestID << " | " << guests[i].name << " | " << guests[i].cnic << " | " << guests[i].phone;
        }
    }
    if (!guestFound) {
        cout << "\nGuest not found!";
    }
}

void displayAllGuest(Guest guests[], int &count) {
    cout << "\nTotal number of guests: " << count;
    cout << "\n==========================\n";
    for (int i = 0; i < count; i++) {
        cout << guests[i].guestID << " | " << guests[i].name << " | " << guests[i].cnic << " | " << guests[i].phone;
        cout << endl;
    }
}

void saveGuests (Guest arr[], int &count) {
    ofstream file("guests.txt");
    if (file.is_open()) {
        file << count << endl;
        for (int i = 0; i < count; i++) {
            file << arr[i].guestID << endl;
            file << arr[i].name << endl;
            file << arr[i].cnic << endl;
            file << arr[i].phone << endl;
        }
        file.close();
        cout << "\nData saved to guests.txt successfully!";
    }
    else {
        cout << "\nFailed to open file. ";
    }
}

void loadGuests (Guest arr[], int &count) {
    ifstream file("guests.txt");
    if (file.is_open()) {
        if (file >> count) {
            if (count > 100)
                count = 100; // safety bound
            for (int i = 0; i < count; i++) {
                file >> arr[i].guestID;
                file.ignore();
                getline(file, arr[i].name);
                file >> arr[i].cnic;
                file >> arr[i].phone;
            }
        }
        file.close();
        cout << "\nData loaded from guests.txt successfully!";
    }
    else {
        cout << "\nguests.txt not found. It will be created upon saving.";
    }
}

//Billing
double calculateBill(double pricePerNight, int nights) {
    double total = pricePerNight * nights;
    return total * 1.05; // 5% tax
}

//Hotel Booking Section
void saveBookings (Booking bookings[], int &count) {
    ofstream file("bookings.txt");
    if (file.is_open()) {
        file << count << endl;
        for (int i = 0; i < count; i++) {
            file << bookings[i].bookingID << endl;
            file << bookings[i].roomNum << endl;
            file << bookings[i].guestID << endl;
            file << bookings[i].nights << endl;
            file << bookings[i].totalBill << endl;
        }
        file.close();
        cout << "\nData saved to bookings.txt successfully!";
    }
    else {
        cout << "\nFailed to open file!";
    }
}

void loadBookings (Booking bookings[], int &count) {
    ifstream file("bookings.txt");
    if (file.is_open()) {
        if (file >> count) {
            if (count > 100)
                count = 100; // safety bound
            for (int i = 0; i < count; i++) {
                file >> bookings[i].bookingID;
                file >> bookings[i].roomNum;
                file >> bookings[i].guestID;
                file >> bookings[i].nights;
                file >> bookings[i].totalBill;
            }
        }
        file.close();
        cout << "\nData loaded from bookings.txt successfully!";
    }
    else {
        cout << "\nbookings.txt not found. It will be created upon saving.";
    }
}

void makeBooking (Room rooms[], Booking bookings[], Guest guests[], int &roomcount, int &bookingcount, int &guestcount) {
    if (bookingcount >= 100) {
        cout << "\nError: Maximum booking database capacity reached!\n";
        return;
    }

    int guestchoice;
    double currentRoomPrice = 100;

    cout << "\n===Welcome to the Skyline Hotel!===\n";
    cout << "\n1. Existing Guest";
    cout << "\n2. New Guest";
    cin >> guestchoice;
    while (guestchoice < 1 || guestchoice > 2) {
        cout << "\nInvalid Option! Re-enter your choice: ";
        cin >> guestchoice;
    }
    if (guestchoice == 1) {
        findGuest(guests, guestcount);
    }
    else {
        addGuest(guests, guestcount);
    }
    cout << "\nEnter the details of your stay at the Hotel.\n";
    cout << "\nBooking ID: ";
    cin >> bookings[bookingcount].bookingID;
    cout << "\nRoom Number: ";
    cin >> bookings[bookingcount].roomNum;

    bool roomValid = false;
    for (int i = 0; i < roomcount; i++) {
        if (rooms[i].roomNum == bookings[bookingcount].roomNum) {
            if (!rooms[i].isAvailable) {
                cout << "\nSorry, this room is already booked!\n";
                return;
            }
            currentRoomPrice = rooms[i].pricePerNight;
            rooms[i].isAvailable = false;
            roomValid = true;
            break;
        }
    }

    if(!roomValid) {
        cout << "\nRoom number not found in system setup!\n";
        return;
    }

    cout << "\nGuest ID: ";
    cin >> bookings[bookingcount].guestID;
    cout << "\nStay In Nights(1-10): ";
    cin >> bookings[bookingcount].nights;
    while (bookings[bookingcount].nights < 1 || bookings[bookingcount].nights > 10) {
        cout << "\nInvalid input. Enter nights between 1 and 10: ";
        cin >> bookings[bookingcount].nights;
    }

    bookings[bookingcount].totalBill = calculateBill(currentRoomPrice, bookings[bookingcount].nights);
    cout << "\nTotal Bill for the complete stay(5% tax included): $" << bookings[bookingcount].totalBill << endl;

    bookingcount++;
    saveBookings(bookings, bookingcount);
}

void cancelBooking(Booking bookings[], Room rooms[], int &bookingcount) {
    int inputID;

    cout << "Enter booking ID to cancel: ";
    cin >> inputID;
    for (int i = 0; i < bookingcount; i++) {
        if (bookings[i].bookingID == inputID) {
            for (int j = 0; j < roomcount; j++) {
                if (rooms[j].roomNum == bookings[i].roomNum) {
                    rooms[j].isAvailable = true;
                    break;
                }
            }
            for (int j = i; j < bookingcount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            bookingcount--;

            saveBookings(bookings, bookingcount);
            cout << "\nBooking Cancelled Successfully! Room is now vacant.";
            return;
        }
    }
    cout << "\nBooking ID not found!";
}

void viewAllBookings(Booking arr[], int count) {
    cout << "\n--- All Bookings Registered ---\n";
    for (int i = 0; i < count; i++) {
        cout << "Booking ID: " << arr[i].bookingID << " | Room: " << arr[i].roomNum
             << " | Guest ID: " << arr[i].guestID << " | Nights: " << arr[i].nights
             << " | Bill Total: $" << arr[i].totalBill << endl;
    }
}

int main () {
    Room rooms[100];
    Booking bookings[100];
    Guest guests[100];

    loadRooms(rooms, roomcount);
    loadBookings(bookings, bookingcount);
    loadGuests(guests, guestcount);
    int choice;

    do {
        cout << "\n\n=====Welcome to the Skyline Hotel!=====";
        cout << "\n1. Add a room";
        cout << "\n2. Display all rooms";
        cout << "\n3. Make a booking";
        cout << "\n4. Cancel a booking";
        cout << "\n5. View all bookings";
        cout << "\n6. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addRoom(rooms, roomcount);
                break;
            case 2:
                displayAllRooms(rooms, roomcount);
                break;
            case 3:
                makeBooking(rooms, bookings, guests, roomcount, bookingcount, guestcount);
                break;
            case 4:
                cancelBooking(bookings, rooms, bookingcount);
                break;
            case 5:
                viewAllBookings(bookings, bookingcount);
                break;
            case 6:
                saveRooms(rooms, roomcount);
                saveBookings(bookings, bookingcount);
                saveGuests(guests, guestcount);
                cout << "\nExiting... Data Saved successfully.\n";
                break;
            default:
                cout << "\nInvalid input choice, try again.";
        }
    } while (choice != 6);

    return 0;
}