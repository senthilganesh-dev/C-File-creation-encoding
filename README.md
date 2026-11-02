# Huffman Coding – C++ Implementation

A simple implementation of the **Huffman Coding algorithm using C++**. This project demonstrates how character frequency analysis, binary trees, sorting, and recursion can be combined to generate variable-length binary codes for characters.

## About the Project

Huffman Coding is a lossless data compression technique that assigns shorter binary codes to frequently occurring characters and longer codes to less frequent characters.

This project builds a Huffman Tree from the input text and generates a unique binary prefix code for each character.

## How It Works

1. **Input:** Accepts a text message from the user.
2. **Frequency Analysis:** Counts the occurrences of each character using `std::map`.
3. **Sorting:** Sorts characters based on their frequencies.
4. **Tree Construction:** Creates leaf nodes and repeatedly merges the two nodes with the lowest frequencies.
5. **Code Generation:** Uses recursive tree traversal to generate binary codes.
6. **Output:** Displays each character, its corresponding Huffman code, and its code length.

## Concepts Used

- Huffman Coding Algorithm
- Binary Tree and Dynamic Memory Allocation
- Recursion and Tree Traversal
- STL Containers: `map`, `vector`, and `pair`
- Sorting and `lower_bound()`
- Lambda Expressions and Comparators
- Structured Bindings (C++17)
- Pointers and Object-Oriented Programming

## Project Structure

```text
Huffman-Coding/
│
├── main.cpp
├── huffman_coding.h
└── README.md
```

## Requirements

- C++17 compatible compiler
- GCC / MinGW / Clang

## Compilation and Execution

Compile using GCC:

```bash
g++ -std=c++17 main.cpp -o huffman
```

Run on Linux:

```bash
./huffman
```

Run on Windows:

```bash
huffman.exe
```

## Sample Output

```text
Enter an msg: hello world

 : 000 : 3
d : 001 : 3
e : 010 : 3
h : 011 : 3
l : 10 : 2
o : 110 : 3
r : 1110 : 4
w : 1111 : 4
```

*Note: Actual codes depend on character frequencies and the tree construction order.*

## Learning Objectives

The main objective of this project is to understand how a theoretical compression algorithm can be implemented using fundamental data structures and C++ STL features.

## Future Improvements

- Implement actual binary encoding and decoding.
- Calculate compression ratio.
- Support file-based compression.
- Improve memory management using smart pointers.
- Handle edge cases and optimize tree construction.

---

**Language:** C++  
**Standard:** C++17  
**Algorithm:** Huffman Coding  
**License:** MIT (if you choose to release it under MIT)
