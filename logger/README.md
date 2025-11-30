# Logger

## Building

Build from project root:
```bash
cd /app/Zenith
cmake -B build -S .
cmake --build build --target logger
```

## Running Tests

```bash
cd /app/Zenith/build/logger
ctest --output-on-failure
```
