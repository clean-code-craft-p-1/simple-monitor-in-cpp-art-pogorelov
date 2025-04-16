## Description

This project is a simple C++ application that simulates a health monitoring system.

The application is agnostic to the type of vital signs it monitors, and it can be extended to support new types of vital
signs in the future by simple editing of the configuration file.

The application reads the config.yml file to determine which vital signs to monitor and their ranges on startup.

Then the user can enter the vital signs values (each vital sign has a unique id) and the application will check if the
values are within the specified range.

If a value is outside the range, the application will print a warning
message.

[Screenshot of the application in action](screenshots\monitor.png) can be found in the **screenshots** directory.

## Extentions

From the beginning, I aimed for a highly flexible design to support future improvements. As a result, it was relatively
easy to extend the functionality. I chose to focus on enhancing configurability through the YAML file.

### Extension 1: Early Warning

The monitor can be extended to support early warning feature per vital. To support this, user should specify the warning
section in the config file.
Since the warning feature is optional, backward compatibility is preserved: this part of the configuration can be
completely removed, and the application will still work correctly. At the same time, to avoid removing parameters and
localization entries from the configuration every time the feature needs to be disabled, there is an **enabled**
setting.

### Extension 2: Support a language in addition to English

Every string that will be shown to the user is localized in the configuration file. The application receives a
command-line argument specifying the locale to use. If a localized version of a string is not available for the given
locale, the default (English) version is used instead.

### Extension 3: Accept input in different units

I believe the simplest way to support different units of measurement is to just add a separate vital in the
configuration file. The thing is, converting between different units can be non-trivial, and the application is, by
design, agnostic to such details. To preserve this flexibility, I don’t want to introduce any conversion logic into the
project.

However, a potential solution could be to implement various transformation algorithms inside a library, and then specify
in the config file which algorithm to use along with its parameters for unit handling. That said, I think this approach
is quite complex.

### Extension idea: UI configuration utility

I like the idea of having a helper utility with a user interface that allows editing the YAML file. A simple dynamic
list with the ability to add, remove, and edit entries would be sufficient.

### YAML configuration example

```yaml
pulse: # Vital sign name
  id: 1               # Unique identifier
  name: # Name of the vital sign, localized below
    en: Pulse
    de: Pulsfrequenz
  min: 60             # Minimum value
  max: 100            # Maximum value
  error_message: # Out of range error message, localized below
    en: Pulse Rate is out of range!
    de: Pulsfrequenz ist außerhalb des Bereichs!
  warning: # Optional early warning section
    enabled: true     # Enable early warning
    tolerance: 1.5    # Tolerance value, used to calculate the warning range
    low_warning: # Low warning message, localized below
      en: Approaching bradycardia!
      de: Näher an Bradykardie!
    high_warning: # High warning message, localized below   
      en: Approaching tachycardia!
      de: Näher an Tachykardie!
```

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
