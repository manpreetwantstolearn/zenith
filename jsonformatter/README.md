# JsonFormatter

## Building

Build from project root:
```bash
cd /app/Zenith
cmake -B build -S .
cmake --build build --target jsonformatter
```

## Running Tests

```bash
cd /app/Zenith/build/jsonformatter
ctest --output-on-failure
```
