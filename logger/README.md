# Logger

## Building

Build from project root:
```bash
cd /app/zenith
cmake -B build -S .
cmake --build build --target logger
```

## Running Tests

```bash
cd /app/zenith/build/logger
ctest --output-on-failure
```
