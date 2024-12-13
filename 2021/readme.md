## Initial setup

```bash
cmake -S . -B build/
cmake --build build
```

## Running

```bash
./build/advent -d[day] -p[part] path/to/input.txt
```

Some older days have their own executables and need to be run indivually, e.g.

```bash
./build/day1-1 path/to/input.txt
```

## Recompiling

```bash
cmake --build build
```

## Debugging

```bash
camke -DCMAKE_BUILD_TYPE=Debug -S . -B build-debug/
cmake --build build-debug

# Then, to debug e.g. day 3, part 1
lldb ./build-debug/advent -- -d2 -p1 path/to/input.txt
```
