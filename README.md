
<div align="center">

<img src="asstes/114514.jpg" width="200" height="200">

<h1>CursorFX</h1>

</div>
CursorFX is a Linux custom animated cursor framework based on Wayland and Ultralight.

The project allows users to create dynamic cursor effects using HTML, CSS, and JavaScript. The rendered content is converted into a native Wayland cursor, enabling customizable and programmable cursor animations.

CursorFX is designed as a lightweight C++ framework that separates cursor rendering, Wayland communication, and configuration management.

---

## Features

- Native Wayland cursor support
- HTML/CSS/JavaScript based cursor themes
- Ultralight rendering backend
- Real-time cursor updates
- Transparent cursor rendering
- Custom cursor animation support


# Dependencies

## Build Dependencies

### Arch Linux

```bash
not yet now :(
```

### Ubuntu / Debian

```bash
not yet now :(
```

---

# Ultralight SDK

CursorFX uses:

```
Ultralight Free SDK 1.4.0
```

Download:

```
https://ultralig.ht/
```

The SDK should be placed as:

```
CursorFX/

 |
 |-- sdk/

      |
      |-- ultralight-free-sdk-1.4.0-linux-x64
```

Expected structure:

```
sdk/
└── ultralight-free-sdk-1.4.0-linux-x64
    |
    |-- include
    |-- lib
    |-- bin
```

---

# Build

Clone repository:

```bash
git clone https://github.com/yourname/CursorFX.git

cd CursorFX
```

Create build directory:

```bash
mkdir build

cd build
```

Configure:

```bash
cmake ..
```

Compile:

```bash
make -j$(nproc)
```

---

# Run

Start CursorFX:

```bash
./build/src/cursor-ani
```
  <p align="center">

## Cursor Editor

A graphical editor for creating cursor animations.

---

## Animation Timeline

Support:

- Keyframes
- Frame interpolation
- Animation curves


---

## Advanced Effects

Possible effects:

- Particle cursor
- Glow effects
- Physics based animation
- Shader effects


---

## Theme Marketplace

Support:

- Theme packages
- Import/export
- Community sharing

---

但是現在還沒做完:)

---

# Author

LuYishan
