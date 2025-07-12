# Stasis OS

**Stasis OS** is a minimal operating system written in C using `i686-elf-gcc`. 
It features a basic terminal, keyboard input handling, VGA text-mode output, ATA disk access, and simple command execution. 
It is designed for educational purposes and low-level OS development.

---

## 🚀 Features

- Bootable ISO with GRUB
- VGA text mode console
- Simple command-line shell
- ATA PIO read/write support
- Keyboard input (scancode to ASCII)
- Sector-based read/write interface
- Basic shell commands (help, clear, reboot, read/write)

---

## 🛠 Requirements

To build and run Stasis OS, make sure you have:

- `i686-elf-gcc` cross compiler  
- `i686-elf-ld` linker  
- `grub-mkrescue` (can be installed in WSL/Ubuntu)
- `qemu-system-i386`  
- Windows Subsystem for Linux (WSL) with Ubuntu  

---

## ▶️ Quick Start (using `run.bat`)

The provided `run.bat` script builds the kernel, creates a bootable ISO, and launches QEMU.

Just run:

```cmd
run.bat
```