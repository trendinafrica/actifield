# Project Description

## Introduction 
The activity meter box is used in neurobehavioral tests to examine the effects of various treatments on the activity level of mice and rats. Our proposed project dubbed “ActiField” is an Arduino-powered activity meter box which can be used to measure locomotor activity of rodents. Locomotor activity is used to evaluate the central effects of drugs. Locomotor activity testing can also reveal possible confounding effects in other tests that rely on motion such as the passive avoidance test for memory. As an additional feature, the ActiField system can be used to automate the open field test, another widely used test for anxiolytic or anxiogenic behaviour. 

## Components
Below is a description of the main components of the ActiField system.

Testing Chamber: The testing chamber is a cuboid plastic box (22×22×30 cm) with a removable transparent cover.

IR Grid: Four panels of 11 IR break beam sensors spaced 2 cm apart are fixed to the inner walls of the testing chamber close to the floor. Each break beam sensor is supplied as a pair of diodes; one diode emits IR beam while the other detects the IR beam. Two panels hold the emitting IR diodes and the other two hold the receiving IR diodes. Receiving and emitting sets will be fixed on opposite sides of the testing chamber to generate a grid of IR beams of 2×2 cm mesh size. As the rodent moves in the testing chamber, the IR beams will be broken and this activity will be transmitted to the microcontroller for processing.

Processing Unit: An Arduino Mega 2560 microcontroller serves as the processor of the system. Inputs from the infrared sensors are fed to the Arduino and processed. The output is displayed online on an attached LCD Screen. Also, a data logging shield is mounted the Arduino for storage of experimental data on an SD. The Arduino can be powered from the mains with a 9 V DC adaptor, a 9 V battery or by a computer.

Display Unit: This consists of a 16×2 LCD screen connected to the Arduino by an i2C LCD backpack. The LCD shows the activity count (total number of beam breaks) and the location of the rodent (centre/periphery) from the system in real time.


## Operation
In our proposed project, ActiField, an Arduino Mega 2560 microcontroller serves as the core processor of the system. Once the code is uploaded to the microcontroller, ActiField can run independently with power from a 9V alkaline battery without the need for a computer or monitor. This is a particularly advantage in settings with erratic or unstable power supply. The system functions automatically and independently according to the code uploaded to the microcontroller. 

Once the system is powered and the code is uploaded, the ActiField system is ready for testing. The mouse or rat to be tested is placed into the test chamber and as the rodent moves in the test chamber it breaks the IR beams in the “grid”. The break beam sensors detect and transmit these signals via the connecting cables to the Arduino. The Arduino keeps a tally of the number of beam breaks and displays the current total on the LCD screen which is mounted on a display unit separate from the test chamber. In most studies, activity counts are expressed at fixed time intervals over the entire test duration. This feature is built into the ActiField system. At a user set frequency (default every 5 min), the Arduino writes the activity count to a file on an SD card mounted on the data logging shield. The user can retrieve this data after the experiment for subsequent analysis on a computer. 
This is the basic functionality of the system however we envisage at least two additional features described below.
Firstly, the ActiField system can be set up to determine the location of the rodent in the test chamber. The IR beams in the test chamber are set up in a grid which represents a coordinate system. Hence, the location of the rodent in the test chamber can be determined based on the set of beams which are broken at a given time. This will require further refinement of the code.
Secondly, the ActiField system can be set up for real time display and graphing of activity counts. This can be made possible by connecting the Arduino to a computer using a USB cable for online display and graphing of the data. We have plans to develop the software to enable this feature using the Processing programming language after building the project. 

## Validation
We intend to validate the system by live video analysis of mice in the test chamber with a video analysis software e.g. Any MAZE or EthoVision concurrently with the ActiField system and comparing the results obtained for correlation.

## Conclusion
In this work, we describe the components and operation of the ActiField system, our proposed real time, automated activity meter box. In this system, low cost components e.g. microcontroller, IR sensors, LCD screen are used to achieve the objectives of the proposed design. 
