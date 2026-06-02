# 🏨 Hotel Booking & Room Management System

A console-based hotel management system written in **C++**, built as a first-semester project. It handles room management, guest records, and bookings — all with file-based persistence across sessions.

---

## ✨ Features

- **Room Management** — Add rooms, view availability, search by room number, and manually toggle availability
- **Guest Management** — Register new guests or look up existing ones by ID
- **Booking System** — Make and cancel bookings with automatic room status updates
- **Billing** — Auto-calculated total bill per stay with 5% tax included
- **Data Persistence** — All data (rooms, guests, bookings) saved to `.txt` files and reloaded on next run

---

## 🗂️ Project Structure

```
hotel-management/
│
├── main.cpp          # Full source code
├── rooms.txt         # Auto-generated: stores room data
├── guests.txt        # Auto-generated: stores guest records
├── bookings.txt      # Auto-generated: stores booking records
└── README.md
```

---

## 🛠️ How to Compile & Run

Make sure you have a C++ compiler installed (e.g. g++).

```bash
g++ main.cpp -o hotel
./hotel
```

On Windows:
```bash
g++ main.cpp -o hotel.exe
hotel.exe
```

---

## 📋 Menu Overview

```
===== Welcome to the Skyline Hotel! =====
1. Add a room
2. Display all rooms
3. Make a booking
4. Cancel a booking
5. View all bookings
6. Exit
```

---

## 🧱 Data Structures Used

| Struct | Fields |
|---|---|
| `Room` | roomNum, roomType, pricePerNight, isAvailable |
| `Guest` | guestID, name, cnic, phone |
| `Booking` | bookingID, roomNum, guestID, nights, totalBill, paymentType |

Arrays of size **100** are used for each — no dynamic memory allocation.

---

## 💾 File Storage Format

Data is stored in plain text files. Example (`rooms.txt`):
```
3
101
Single
50.00
1
102
Double
80.00
0
```

---

## ⚠️ Current Limitations

> *(These are being addressed in upcoming updates)*

- No login/authentication system
- Room cap fixed at 100 (static arrays)
- `paymentType` field in `Booking` struct is declared but never used
- No date-based check-in / check-out tracking
- Guest IDs are manually entered (no auto-increment)
- No duplicate booking ID or guest ID validation

---

## 🚧 Planned Improvements

- [ ] Fix `paymentType` — prompt user during booking and save it
- [ ] Add duplicate ID validation for guests and bookings
- [ ] Add auto-increment IDs
- [ ] Add check-in / check-out date fields
- [ ] Add guest update/delete functionality
- [ ] Input sanitization and error handling improvements

---

## 👤 Author

**Syed Shaheer Ali**  
BS Computer Science — Bahria University, Karachi Campus

---

## 📄 License

This project is open for academic and personal use.
