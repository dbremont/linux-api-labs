# 📜 Source Code

> ...

## 🚀 Build

- 🛠️ g++ counter.cpp -o gtk_app `pkg-config --cflags --libs gtk+-3.0`
- ⚡ valac --pkg gtk4 counter.vala

## Dissambler

- `gcc -o disassembler disassembler.c -lcapstone`
- ./disassembler `<binary file>`
