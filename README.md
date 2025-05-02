# ✈️ Aero Assault (SFML + C++)

Aero Assault is a fast-paced 2D plane combat game built using C++ and SFML (Simple and Fast Multimedia Library). Battle enemy aircraft, dodge incoming fire, and power through waves in this classic-style arcade shooter.

---

## 🚀 Features

- 2D vertical-scrolling plane shooter
- Player and enemy aircraft with basic AI
- Bullet firing.
- Health and scoring system
- Difficulty increases at third wave (boss fight)
- Built with SFML for smooth graphics and input

---

## 🛠️ Installation

### Step 1: Install SFML

```bash
sudo apt update
sudo apt install libsfml-dev
g++ main.cpp -o aero-assault -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./aero-assault
