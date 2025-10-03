# 03-10-2025 IO as Part of the Infrastructure Layer

## Context and Problem Statement

The project requires implementation of input/output (I/O) operations — such as access to video memory, keyboard input, hardware ports, and other low-level device interactions.
It is necessary to determine where I/O-related code should reside in the system architecture: within the domain layer, utilities, or the infrastructure layer.
Determening VGA driver as a "special" independent part of I/O system

## Considered Options

* Application
* Infrastructure

## Decision Outcome

Chosen option: "Infrastructure", because I/O system is cpu architecture dependant and need to be implmeneted multiple times
Separating I/O simplifies testing of domain logic.
It allows for mocking, simulation, or replacement of I/O in test or alternate runtime environments.
Moving VGA to infrasturcture allows making a unified interface for different video standards. ARM and RISC-V have no VGA mode, so vga is hardware dependant
