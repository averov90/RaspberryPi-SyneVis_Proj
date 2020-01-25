# Raspberry - Synesthesia Vision
[![License](https://img.shields.io/badge/LICENSE-The%20Unlicense-green?style=flat-square)](/LICENSE)  [![Version](https://img.shields.io/badge/VERSION-DEBUG%20--%20demonstrable-yellow?style=flat-square)](https://github.com/averov90/RaspberryPi-SyneVis_Proj/releases)
### :small_orange_diamond: [Русская версия](/README.md)
This project in its final form is a device of the following configuration:
- Raspberry Pi (with raspbian installed, libraries, and, in fact, the program)
- Raspicam (1080p)
- Sonar sensor (HC-SR04)
- 2 buttons
- controlled illumination
- vibration motor

**ATTENTION:** This is an experimental project, the creation of which was caused by my desire to experiment with the Google API, Raspberry Pi, as well as some new concepts for me (for example, vision through hearing). DO not regard it as a real prototype or a practical device! This device was created exclusively for entertainment purposes, and the area of the problem "solved" by the device was selected based on the components that made me want to experiment (the same Google Vision API). If you're careful, you will not find, for example, any algorithms of the image analysis (to determine the color in the simplest case, it would be appropriate to begin to define the contours of the gradients, and then to operate with Cetra masses and squares contours and shift with respect to the center of the frame) nor the neural network (which, by the way, in the case of this project, whether he is a prototype, - to use no reason at all). This is because there was no such need for this project, because the goal was not to create a prototype, but to experiment with components, which was a success.

### *This project was created based on: [Synesthesia Vision](https://github.com/averov90/Synesthesia-Vision).*

*P.S. Now this device has been disassembled and it happened that the latest version of the code remained on it and was lost after formatting the sd card. This was discovered relatively recently. So I have laid out code, though a work, is not complete in terms of functionality (collaboration blocks), i.e. not the written code that creates a "state machine" from the blocks and runs it (by the way, append this code is not difficult since all points of principle have already been implemented and appending moved into the category of routine tasks). The blocks themselves in this version, of course, are already ready. If someone is interested in this experiment and wants to add it to the final state, I will be happy to accept the Pull request.*
