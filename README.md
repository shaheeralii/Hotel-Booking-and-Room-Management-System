# Hotel Booking & Room Management System
![GitHub repo size](https://img.shields.io/github/repo-size/shaheeralii/Hotel-Booking-and-Room-Management-System)
![GitHub last commit](https://img.shields.io/github/last-commit/shaheeralii/Hotel-Booking-and-Room-Management-System)
![GitHub stars](https://img.shields.io/github/stars/shaheeralii/Hotel-Booking-and-Room-Management-System)

A console-based hotel management application written in C++. It manages rooms, guests, and bookings for a single hotel — Skyline Hotel — with automatic bill calculation and file-based persistence between sessions.


## Overview

The system runs as a menu-driven console loop. On startup it loads any previously saved room, guest, and booking data from disk; on exit it writes the current in-memory state back to disk. Within a session, the user can register rooms, create or cancel bookings (which registers or looks up a guest as part of the flow), and view current bookings — with each booking's cost calculated automatically from the room's nightly rate and the tax rate.

## Features

| Area | Functionality |
|---|---|
| Room Management | Add new rooms; display all rooms with live availability count |
| Guest Management | Register a new guest or look up an existing guest by ID (as part of the booking flow) |
| Booking | Create a booking against an existing, available room; auto-generates a bill |
| Cancellation | Cancel a booking by ID, which frees the associated room and removes the record |
| Billing | Total cost computed as `price × nights`, plus a fixed 5% tax |
| Persistence | Rooms, guests, and bookings are saved to and loaded from separate `.txt` files |

## Menu Overview

The main loop exposes six options:

```text
=====Welcome to the Skyline Hotel!=====
1. Add a room
2. Display all rooms
3. Make a booking
4. Cancel a booking
5. View all bookings
6. Exit
```

Selecting **Make a booking** first prompts whether the guest is existing (searched by ID) or new (registered on the spot), then collects a booking ID, room number, guest ID, and length of stay before calculating and printing the total bill.

## Technical Implementation

- **Structures** — `Room`, `Guest`, and `Booking` model the core entities, each held in a fixed-size array of 100 in `main()` and passed to functions by array pointer, with counts tracked via reference parameters (`int &count`).
- **No dynamic memory** — all storage uses stack-allocated arrays; there is no use of `vector`, `new`, or dynamic containers.
- **File I/O** — each entity has a dedicated `save`/`load` function pair using `ofstream`/`ifstream`, with `cin.ignore()` / `file.ignore()` used to safely mix `>>` and `getline()` when reading names and room types.
- **Input validation** — menu choices, room numbers, availability toggles, and stay length (1–10 nights) are validated with retry loops; booking existence and room availability are checked before a booking is confirmed.
- **Array-based deletion** — cancelling a booking removes it by left-shifting subsequent elements over the deleted index, rather than using an erase-capable container.

**Note:** `searchRoom()` and `updateAvailability()` (room lookup and manual availability toggling) and `displayAllGuest()` are implemented in the source but are not wired into the main menu, so they aren't currently reachable during a normal run.

## Data Structures

| Structure | Purpose | Fields |
|---|---|---|
| `Room` | Represents a hotel room | `roomNum`, `roomType`, `pricePerNight`, `isAvailable` |
| `Guest` | Represents a guest record | `guestID`, `name`, `cnic`, `phone` |
| `Booking` | Represents a booking record | `bookingID`, `roomNum`, `guestID`, `nights`, `totalBill`, `paymentType` |

`paymentType` is declared on `Booking` but is never set, saved, or displayed anywhere in the program.

## Data Persistence

Each entity is stored in its own plain-text file in the project root, written on exit (and after every booking or cancellation) and read back on startup.

| File | Contents |
|---|---|
| `rooms.txt` | Record count, followed by `roomNum`, `roomType`, `pricePerNight`, `isAvailable` (0/1) per room |
| `guests.txt` | Record count, followed by `guestID`, `name`, `cnic`, `phone` per guest |
| `bookings.txt` | Record count, followed by `bookingID`, `roomNum`, `guestID`, `nights`, `totalBill` per booking |

Example (`rooms.txt`):

```text
2
101
Single
50.00
1
102
Double
80.00
0
```

## Project Structure

Initial
```text
Hotel-Booking-and-Room-Management-System/
├── main.cpp        # Full source code
├── .gitignore        # Excludes generated and unnecessary files from Git
└── README.md
```
After running program locally
```text
Hotel-Booking-and-Room-Management-System/
├── main.cpp        # Full source code
├── .gitignore      # Excludes generated and unnecessary files from Git
├── rooms.txt       # Generated room data
├── guests.txt      # Generated guest data
├── bookings.txt    # Generated booking data
└── README.md       # Project documentation
```

## Build & Run

```bash
g++ main.cpp -o hotel
./hotel
```

On Windows:

```bash
g++ main.cpp -o hotel.exe
hotel.exe
```

## Requirements

- A C++ compiler (e.g. g++), C++11 or later
- C++ standard library only — no external dependencies
- Read/write access to the working directory for the three `.txt` data files

## Limitations

- No login or authentication system
- Fixed capacity of 100 records each for rooms, guests, and bookings (static arrays)
- `paymentType` field on `Booking` is declared but never used
- No date-based check-in/check-out tracking — stay length is a plain night count
- Room, guest, and booking IDs are entered manually with no auto-increment
- No duplicate-ID validation for rooms, guests, or bookings
- During booking, guest ID is re-entered manually rather than being taken automatically from the guest just found or registered
- `searchRoom()`, `updateAvailability()`, and `displayAllGuest()` exist but are not exposed through the menu

## Planned Improvements

- [ ] Wire `searchRoom()`, `updateAvailability()`, and `displayAllGuest()` into the main menu
- [ ] Prompt for and persist `paymentType` during booking
- [ ] Add duplicate-ID validation for rooms, guests, and bookings
- [ ] Auto-increment IDs instead of manual entry
- [ ] Add check-in/check-out date fields
- [ ] Automatically link the guest found/registered during booking to the booking's `guestID`

## Technologies Used

| Technology | Usage |
|---|---|
| C++ | Core application logic |
| Standard Library (`<iostream>`, `<string>`, `<fstream>`) | Console I/O and file-based persistence |

## Author

**Syed Shaheer Ali**
BS Computer Science — Bahria University, Karachi Campus

## License

This project is open for academic and personal use.
