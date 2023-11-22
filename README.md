# IntroductionToRobotics
This GitHub repository contains my third-year robotics class projects and homework assignments, primarily focused on Arduino-based projects. It serves as a portfolio of my work throughout the course, showcasing my progress and skills in the field of robotics and embedded systems.
# Welcome to my Robotics Class Projects Repository

Hey there! 👋 Welcome to my GitHub repository where I've documented my journey through the exciting world of robotics and embedded systems as a third-year student at CTI (Faculty of Mathematics and Informatics - Computer and Technology Information).

## About this Repository

This repository is a collection of my coursework, homework assignments, and personal projects related to robotics, with a strong emphasis on Arduino-based creations. It's my way of showcasing the knowledge and skills I've acquired during my time in the robotics class.

## What You'll Find Here

- **Homework Assignments:** You'll find a record of my homework submissions, complete with documentation and code.
- **Projects:** I've taken on various projects throughout the course. Each project is well-documented and includes source code, circuit diagrams, and explanations.
- **Learning Progress:** In the form of commits, you can witness my learning journey and how I've improved over time.

## How to Navigate

Feel free to explore the folders and projects available in this repository. Here are a few quick pointers to help you navigate:

- **Homework:** Check the 'Homework' directory for my homework submissions.
- **Projects:** The 'Projects' directory contains the larger, more creative undertakings and the final project.
- **Labs:** The 'Labs' directory contains the code that we do in the lab.
- **Commits:** If you're curious about my learning process, take a look at the commit history.

## Homework 1
-  **This is the sanity check**, I've attached the code and I will attach a picture in the folder too
-  I have three potentiometers that control the intensity of three LED lights
-  My RGB led wasnt working so i've used three LED's, the result is the same basically
-  Cool video that shows how it works: https://youtube.com/shorts/XgWn5MQpkdY?si=5zMGLWPp5IPT6B9z

## Homework 2
- An elevator simulator, it *kinda* works
- I've attached the code and a video of it working

## Homework 3
- A joystick that controls a 7 segment display


## Homework 4
<details>
  <summary><b>Lap Counter Arduino</b></summary>

  This Arduino code is designed for a lap counter application using a 4-digit 7-segment display and a button to increment the lap count.

  ### Components

  - **Hardware:**
    - 4-digit 7-segment display with specific pin connections.
    - Button for lap counting.
    - Debounce logic to prevent button noise.

  ### Functionality

  - The code counts laps and displays the lap number on the 7-segment display.
  - It utilizes a button with debounce logic for lap counting.
  - The lap number is displayed on the 4-digit 7-segment display.
  - It has a pause button to pause the current lap
  - It has a previous lap to return to the previous lap time

  ### Code Structure

  - **Constants and Pin Definitions:** The code defines pin connections and arrays for 7-segment display segments and encodings.

  - **Setup:** Initializes pin modes, sets an initial display state, and initializes the Serial communication.

  - **Loop:** 
    - Handles button press and debounce.
    - Updates the lap count and number displayed on the 7-segment display.
    - Prints the combined lap number and value on the Serial monitor.

  - **Functions:**
    - `writeReg(int digit)`: Writes data to the 7-segment display.
    - `activateDisplay(int displayNumber)`: Activates a specific digit in the 7-segment display.
    - `writeNumber(int number)`: Writes the lap number to the display, handling multiple digits.

  - [**Video:**](https://youtu.be/dszb2ST7NYs) 
</details>
