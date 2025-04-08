## Description

This project is a simple C++ application that simulates a health monitoring system.

The application is agnostic to the type of vital signs it monitors, and it can be extended to support new types of vital
signs in the future by simple editing of the configuration file.

The application reads the config.yml file to determine which vital signs to monitor and their ranges on startup.

Then the user can enter the vital signs values (each vital sign has a unique id) and the application will check if the
values are within the specified range.

If a value is outside the range, the application will print a warning
message.

## Development

### Build and run

Since git submodules are used, you need to execute the following command before trying to build the project:

```bash
git submodule update --init --recursive
```

Then, you can build the project using the standard CMake commands:

```bash
cmake -S . -B build
cmake --build build
```

### Dependencies

This project uses the following dependencies (see **external** directory):

- [CLI11](https://github.com/CLIUtils/CLI11.git )
- [yaml-cpp]( https://github.com/jbeder/yaml-cpp.git )
- [googletest](https://github.com/google/googletest.git)
- [rapidcheck](https://github.com/emil-e/rapidcheck.git )

# Programming Paradigms

Health Monitoring Systems

[Here is an article that helps to understand the Adult Vital Signs](https://en.wikipedia.org/wiki/Vital_signs)

[Here is a reference to Medical monitoring](https://en.wikipedia.org/wiki/Monitoring_(medicine))

## Purpose

Continuous monitoring of vital signs, such as respiration and heartbeat, plays a crucial role in early detection and
prediction of conditions that may affect the wellbeing of a patient.

Monitoring requires accurate reading and thresholding of the vitals.

## Issues

- The code here has high complexity in a single function.
- The code is not modular
- The tests are not complete - they do not cover all the needs of a consumer

## Tasks

1. Reduce the cyclomatic complexity.
1. Separate pure functions from I/O
1. Avoid duplication - functions that do nearly the same thing
1. Complete the tests - cover all conditions.

## Self-evaluation

How well does our code hold-out in the rapidly evolving [WHDS](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6111409/)?
Can we add future functionality without disturbing existing features? Can we do it with low effort and high reliability?

## The future

- May need new vital signs
- A vendor may provide additional vital readings (e.g., blood pressure)
- Limits may change based on the age of a patient

> Predicting the future requires Astrology!

## Keep it simple and testable

Shorten the Semantic distance

- Procedural to express sequence
- Functional to express relation between input and output
- Object oriented to encapsulate state with actions
- Apect oriented to capture repeating aspects
