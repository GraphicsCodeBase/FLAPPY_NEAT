---
name: flappyneat-build
description: >
  Builds the FlappyNEAT C++/OpenGL project using CMake and vcpkg. Use this skill
  whenever the user says "build", "compile", "let's build", "/build", "does it compile",
  "run a build", or any time code changes need to be compiled and tested. Also trigger
  after implementing any new system or making changes to .cpp/.h files in the FlappyNEAT
  project. This skill knows the exact CMake + vcpkg configuration for this project.
---

# FlappyNEAT Build Skill

You are building the FlappyNEAT project — a C++17 OpenGL game using CMake and vcpkg on Windows.

## Project details

- **Root:** `C:\Users\Micro\Desktop\Personal_Projects\NEW_SECRET_PROJECT\Repo\FLAPPY_NEAT`
- **Toolchain:** `C:/vcpkg/scripts/buildsystems/vcpkg.cmake`
- **Build dir:** `out/build`
- **Exe:** `out/build/Release/FlappyNEAT.exe`

## Steps

### 1. Configure (only if needed)

Check whether `out/build/CMakeCache.txt` exists. If it does, skip to step 2. If it doesn't, run configure:

```
cmake -B out/build -S . -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

Run this from the project root. If it fails, report the error and stop — a configure failure usually means vcpkg is missing a package.

### 2. Build

```
cmake --build out/build --config Release
```

### 3. Report result

**On success:**
Tell the user the build succeeded and the exe is ready at:
`out/build/Release/FlappyNEAT.exe`

**On failure:**
- Extract only the actual compiler errors (lines containing `error:`) from the output — don't dump the full log
- Group errors by file
- State clearly which file and line the error is on
- If the error is something you can fix (missing include, typo, wrong type), fix it and rebuild automatically
- If you need the user's input to fix it, explain what's wrong in plain terms

## Important notes

- Always run commands from the project root directory
- Use `--config Release` not Debug — the game needs Release for reasonable performance
- If CMakeCache.txt exists but the build fails with "could not find package", delete `out/build/` and re-run configure (vcpkg packages may have been added since last configure)
