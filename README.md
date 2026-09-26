# 🧠 Team Beta — Cognitive & Psychological Awareness Games

A beginner-friendly **C programming project** that uses simple interactive games to demonstrate different aspects of **attention, reaction time, memory, language, and cognitive processing**.

The project contains **5 different cognitive/psychological themes**, with **2 games under each theme**.

> ⚠️ **Important:** This project is created for educational, research-demonstration, and awareness purposes only. The games are **not medical tests and cannot diagnose any disorder or psychological condition**.

---

## 🎯 Project Overview

The main menu allows the user to select one of five categories:

| No. | Theme                               | Game 1                | Game 2              |
| --- | ----------------------------------- | --------------------- | ------------------- |
| 1   | Major Depressive Disorder           | Number Spotter        | Reaction Timer      |
| 2   | Stroke-Related Cognitive Impairment | Word Scramble         | C Programming Quiz  |
| 3   | Developmental Language Disorder     | Word Picture Matching | Sentence Completion |
| 4   | Generalized Anxiety Disorder        | Dot-Probe Task        | Colour Word Quiz    |
| 5   | Dyslexia                            | Letter Swap           | Rhyming Word Game   |

Each game is designed to demonstrate a particular type of cognitive task using a simple **command-line interface**.

---

# 🎮 Games Included

## 1️⃣ Major Depressive Disorder

### 🔢 Number Spotter

The player is shown a list of numbers and must identify the position of a target number.

Features:

* Increasing list size
* Different difficulty levels
* Time-based scoring
* Hints
* Wrong-answer limit
* Streak bonuses
* Final score and best streak

### ⚡ Reaction Timer

The player waits for a random delay and then presses Enter as quickly as possible.

Features:

* Reaction-time measurement
* Multiple difficulty levels
* Up to 20 rounds
* Best/worst/average reaction time
* Streak system
* Session statistics

---

# 2️⃣ Stroke-Related Cognitive Impairment

### 🔤 Word Scramble Game

The player is given a scrambled word and chooses the correct answer from multiple options.

The game records:

* Correct/incorrect answers
* Reaction time
* Score

### 💻 C Programming Quiz

A simple multiple-choice quiz based on basic C programming concepts.

Topics include:

* C programming language
* `printf()`
* Data types
* C statements
* Loops

---

# 3️⃣ Developmental Language Disorder

### 🖼️ Word Picture Matching

The player matches a word with the corresponding numbered picture/object.

The game contains:

* 20 objects
* 20 questions
* Score tracking
* Multiple rounds

### 📝 Sentence Completion

The player completes sentences by selecting the appropriate word.

The questions test basic:

* Vocabulary
* Prepositions
* Conjunctions
* Sentence relationships
* Basic language understanding

The final score is displayed out of 20.

---

# 4️⃣ Generalized Anxiety Disorder

## Threat Bias & Hypervigilance

### 🎯 Dot-Probe Task

The Dot-Probe Task presents two words:

* Positive/neutral words
* Negative/threat-related words

The words appear on the left and right side of the screen. After they disappear, the player is asked about the position of one of the words.

The player responds using:

* ⬅️ **Left Arrow** — word was on the left
* ➡️ **Right Arrow** — word was on the right

The program records:

* Correct responses
* Reaction time
* Average reaction time for positive words
* Average reaction time for threat-related words

### 🎨 Colour Word Quiz

This game is inspired by the idea of **colour-word interference tasks**.

A word is displayed and the player must identify its colour while ignoring the meaning of the word.

Available colours:

```text
1 = RED
2 = GREEN
3 = BLUE
4 = YELLOW
```

The game records:

* Correct responses
* Reaction time
* Average reaction time
* Comparison between positive/neutral and threat-related word trials

---

# 5️⃣ Dyslexia

### 🔄 Letter Swap Game

The player selects a word and must rearrange its letters to form another word.

Example:

```text
CAT → ACT
DOG → GOD
BAT → TAB
```

The program records:

* Correct/incorrect answer
* Reaction time
* Score

### 🎵 Rhyming Word Game

The player is given a word and must type a suitable rhyming word.

Example:

```text
CAT → HAT
DOG → FOG
```

The game includes multiple rounds and calculates the total score.

---

# 🛠️ Technologies Used

The project is written in:

**C Programming Language**

Main concepts used:

* Variables
* `if`, `else if`, `else`
* `switch`
* `for` loops
* `while` loops
* Functions
* Arrays
* Strings
* Random number generation
* Time measurement
* `clock()`
* `rand()`
* `srand()`
* `scanf()`
* `printf()`
* `strcmp()`
* Dynamic memory allocation
* Basic input handling

Windows-specific libraries are also used:

```c
#include <conio.h>
#include <windows.h>
```

These provide functions such as:

```c
getch()
Sleep()
```

---

# 💻 How to Run

## Requirements

* Windows operating system
* A C compiler
* Dev-C++ / Code::Blocks / similar C IDE

## Running with Dev-C++

1. Open **Dev-C++**.
2. Create a new C source file.
3. Paste the project code.
4. Save the file with a `.c` extension.
5. Compile the program.
6. Run the executable.
7. Use the main menu to select a category.

---

# 📂 Project Structure

The project is organized using separate functions for each game.

```text
Team Beta Cognitive Games
│
├── Major Depressive Disorder
│   ├── Number Spotter
│   └── Reaction Timer
│
├── Stroke-Related Cognitive Impairment
│   ├── Word Scramble
│   └── C Programming Quiz
│
├── Developmental Language Disorder
│   ├── Word Picture Matching
│   └── Sentence Completion
│
├── Generalized Anxiety Disorder
│   ├── Dot-Probe Task
│   └── Colour Word Quiz
│
└── Dyslexia
    ├── Letter Swap
    └── Rhyming Word Game
```

---

# 🧩 Project Objective

The objective of this project is to demonstrate how basic programming concepts can be used to create interactive tasks related to:

* Attention
* Reaction time
* Memory
* Language processing
* Word recognition
* Cognitive flexibility
* Response accuracy

The project also demonstrates how data such as **reaction time and accuracy** can be collected and displayed during a simple computer-based experiment.

---

# 📊 What the Project Demonstrates

The project combines programming with basic concepts from cognitive psychology.

For example:

```text
Stimulus
   ↓
User observes information
   ↓
User makes a response
   ↓
Program records response
   ↓
Reaction time / accuracy calculated
   ↓
Results displayed
```

This provides a simple demonstration of how computer-based cognitive experiments can be implemented.

---

# ⚠️ Disclaimer

This project is **not a clinical assessment tool**.

The results produced by these games should **not** be interpreted as a diagnosis of:

* Major Depressive Disorder
* Stroke-related cognitive impairment
* Developmental Language Disorder
* Generalized Anxiety Disorder
* Dyslexia

Reaction time and game performance can be affected by many factors such as familiarity with computers, attention, environment, practice, input devices, and individual differences.

The project is intended only for **educational, programming, awareness, and demonstration purposes**.

---

# 👨‍💻 Team

### Team Beta

**Project developed using C Programming Language**

This project was created as a beginner-level programming project demonstrating the application of C programming to interactive cognitive tasks.

---

# 🚀 Future Improvements

Possible future versions could include:

* Graphical user interface
* Better reaction-time measurement
* More randomized questions
* Larger word databases
* Data saving to files
* CSV result export
* Graphs of reaction times
* User profiles
* More difficulty levels
* Improved keyboard input handling
* More scientifically controlled experimental conditions

---

## ⭐ Conclusion

**Team Beta — Cognitive & Psychological Awareness Games** demonstrates how a simple C program can combine programming concepts with interactive cognitive tasks.

The project focuses on making these concepts understandable through **simple games, reaction-time measurements, scoring systems, and interactive experiments**.

> **Built with C • Designed for learning • Created for awareness**
