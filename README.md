# Final Project for C++

For the C++ course you will have to build a nice app/game on your own.

**DEADLINE: 4th of January.** Doesn't mean you should build the app in december. Final touches can be made then.

All code should be placed inside this git project and be accompanied by a README and Makefile.

Choose 1 of the assignment options and inform your teacher about your choice.

## Option 1 - Tetris

Build a console Tetris clone. Make sure the player's score is tracked in a scoreboard (save as json file for example).

Extra's could be a 2-player game.

## Option 2 - Snake

Build a Snake clone. Make sure the player's score is tracked in a scoreboard (save as json file for example). Allow the map that is played to be loaded from a file (make up your own format).

Extra could be a map editor to create maps.

## Options 3 - CLI ChatApp

Build a chat application that works from the terminal. Allow people to create/join channels in which they can chat. Also allow private messages.

For communication, several options exists: TCP Sockets, MQTT, ...

## Options 4 - Challenge Checker

Programming courses often come with challenges to solve. Create an application that can check the challenges that were solved. You can focus on C++ applications that run from the terminal.

Each challenge is accompanied by a markdown file that contains the description of the challenge to solve and some front matter (extra information header), for example:

``````markdown
---
name: sorting-101
description: Sort the numbers in the array from small to large
difficulty: medium
solved: true
executable: sort
build: g++ main.cpp -o sort
---

# Sorting 101

Sort the numbers in the array from small to large

## Expected Output

```
Welcome to number sort.
Sorting ...

1 5 12 234 543 21234
```
```

``````

The output to be checked and expected from the challenge can always be found beneath a level 2 markdown heading as the last section in the `README.md` file.

Request more information from the teacher if you choose this option.

## General

- The whole app/game should be object oriented. No global stuff. Main should also be clean.
- Code should be your own. You can research techniques and such but no code copy pasting. If teacher finds out (and he/she does 9 out of 10 times), the other guy/girl gets the grades and not you.
- Decent GIT history so teacher can track your progress through time. This means committing often and committing small. This is also part of proving your code is your own.
- Provide a decent README explaining your project, how it is structured, what fancy techniques you used, how someone can build your app and how to run it. Also add a couple of screenshots in your README off how your app looks.
- A makefile so the user only needs to use `make` to build your app.
- Check if your application runs on other systems (Windows vs Linux). If not, no problem, but make sure to document this inside your README.
