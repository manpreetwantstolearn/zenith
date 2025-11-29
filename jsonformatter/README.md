# JsonFormatter

## Building

Build from project root:
```bash
cd /app/zenith
cmake -B build -S .
cmake --build build --target jsonformatter
```

## Running Tests

```bash
cd /app/zenith/build/jsonformatter
ctest --output-on-failure
```
