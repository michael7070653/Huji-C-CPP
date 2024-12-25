
# Markov Chain Project: Tweet Generator

## Overview
This project implements a **Markov Chain-based Tweet Generator**. Using a provided dataset of tweets, the program generates new, realistic-sounding tweets by analyzing word sequences and constructing a probability-based language model.

The repository also demonstrates key programming concepts such as:
- **Markov Chains** for modeling sequences and probabilities.
- **Linked List Management** for dynamic data storage and traversal.
- A fun addition: **Snakes and Ladders**, showcasing simulation in C.

The main focus is the tweet generator, which highlights the flexibility and power of Markov chains for natural language processing tasks.

---

## Features
- **Markov Chain Implementation**:
  - Generates text based on a Markov chain algorithm.
  - Trains the model using a dataset (`justdoit_tweets.txt`).
- **Linked List Library**:
  - Provides custom linked list structures for managing chains of words.
- **Snakes and Ladders**:
  - A standalone implementation of the classic game, included as a bonus.

---

## File Structure
- **Source Code**:
  - `tweets_generator.c`: Main program for generating tweets.
  - `markov_chain.c` & `markov_chain.h`: Core implementation of the Markov chain.
  - `linked_list.c` & `linked_list.h`: Helper library for linked list operations.
  - `snakes_and_ladders.c`: Implementation of the Snakes and Ladders game.

- **Build Configuration**:
  - `CMakeLists.txt`: CMake configuration for compiling the project.
  - `makefile`: Alternative build configuration using Make.

- **Input Data**:
  - `justdoit_tweets.txt`: Example dataset used to train the Markov chain.

---

## Installation
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```
2. Build the project:
   - Using **CMake**:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```
   - Using **Make**:
     ```bash
     make
     ```

---

## Usage
1. Run the tweet generator:
   ```bash
   ./tweets_generator
   ```
   This will generate tweets based on the dataset in `justdoit_tweets.txt`.

2. (Optional) Play Snakes and Ladders:
   ```bash
   ./snakes_and_ladders
   ```

---

## Dependencies
- A C compiler (e.g., GCC or Clang).
- CMake (optional, for building the project).

---

## Contribution
Contributions are welcome! Please:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request with a detailed explanation of your changes.

---

## License
This project is licensed under the MIT License. Feel free to use and modify the code.
