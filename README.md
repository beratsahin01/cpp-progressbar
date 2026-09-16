# C++ Terminal Progress Bar

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Type](https://img.shields.io/badge/Header--Only-Ready-brightgreen)

A lightweight, header-only, ANSI-colored terminal progress bar library for modern C++. It provides real-time progress visualization, throughput metrics (`it/s`), elapsed time, and ETA calculations with zero external dependencies.

---

## Features

- **Header-Only:** Drop `progressbar.hpp` into your include directory and start using it.
- **Zero Dependencies:** Pure C++17 standard library implementation.
- **Real-Time Metrics:** Dynamic computation of throughput (`it/s`), elapsed runtime, and Estimated Time of Arrival (ETA).
- **ANSI Styling:** Integrated terminal colors (green filled bar, yellow head indicator, cyan throughput).
- **Clean Terminal Output:** Employs carriage return (`\r`) with padding buffers to eliminate flickering and trailing text artifacts.

---

## Preview

```text
[==============>               ]  50% | 100/200 | 48.6 it/s | Elapsed: 00m:02s | ETA: 00m:02s
