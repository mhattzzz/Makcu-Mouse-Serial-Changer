# Makcu Mouse Serial Changer

## Overview

Makcu Mouse Serial Changer is a lightweight Windows console application written in C++.  
It connects to a Makcu device and allows you to:

- Read the current mouse serial
- Generate a new random serial (8–11 characters)
- Apply a new serial to the device
- Reset the serial to its default value

The project uses the **makcu-cpp** library for device communication:  
https://github.com/K4HVH/makcu-cpp

This project is intended for educational and research purposes.

---

## Features

- Random uppercase alphanumeric serial generation
- Configurable serial length (8–11 characters)
- Enforced ending convention:
  - `8` → Device serial
  - `9` → Box serial
- Serial reset support
- High performance mode enabled
- Simple command-line interface
- Minimal external dependencies

---

## Dependencies

- Windows OS
- C++17 compatible compiler
- Makcu device
- makcu-cpp library  
  https://github.com/K4HVH/makcu-cpp

---

## Project Structure

```

Makcu-Mouse-Serial-Changer/
│
├── src/
│   └── main.cpp
│
├── Makcu/
│   └── include/
│
├── README.md
└── .gitignore

```

---

## How It Works

### 1. Device Initialization

The application:

- Searches for connected Makcu devices using makcu-cpp
- Connects to the first detected device
- Enables high performance mode
- Enables profiling

If no device is found, the program exits safely.

---

### 2. Serial Generation

Serials are generated using:

- `std::mt19937` random engine
- Uppercase alphanumeric character set
- Configurable length between 8 and 11 characters
- Forced ending digit rule

Example generated serial:

```

A7XK29LMQ8

```

---

### 3. Serial Update Process

The program:

1. Retrieves the current serial
2. Prompts the user for the desired length
3. Generates a new serial (or resets if `0` is entered)
4. Applies the serial using makcu-cpp API
5. Verifies the change
6. Displays the result

---

## Usage

Compile the project and run the executable.

When prompted:

```

Type the desired serial length (8–11)
Type 0 to reset the serial

```

Example flow:

```

(-) Current Mouse Serial: ABCD12348

(.) Type the desired serial length: 10

(+) Successfully changed your mouse serial
(-) New Mouse Serial: ZYXW987658

```

---

## Build Instructions (Visual Studio)

1. Clone or download the makcu-cpp repository  
   https://github.com/K4HVH/makcu-cpp

2. Add the makcu-cpp include directory to your project

3. Create a new C++ Console Application

4. Set the language standard to C++17

5. Add `main.cpp`

6. Build in x64 mode

---

## Technical Notes

- Uses thread-local random engine
- Prevents invalid serial lengths
- Includes basic runtime validation
- Windows-only (uses `Windows.h`)
- Built on top of the makcu-cpp device communication layer

---

## Disclaimer

This software is provided for educational and research purposes only.

Modifying hardware identifiers may violate manufacturer policies, platform rules, or local regulations.  
The author assumes no responsibility for misuse or any resulting consequences.

Use responsibly and at your own risk.

---

## License

MIT License

You are free to use, modify, and distribute this software under the terms of the MIT License.
