# 📝 08 — File Handling Notes

## Key Classes
- `ifstream` — input (reading) file stream
- `ofstream` — output (writing) file stream
- `fstream`  — both read and write

## Open Modes
| Mode | Meaning |
|------|---------|
| `ios::in`     | Read |
| `ios::out`    | Write (overwrites) |
| `ios::app`    | Append |
| `ios::binary` | Binary mode |
| `ios::trunc`  | Truncate (clear) |

## Always close files! Or use RAII (file closes in destructor)

## Common pitfall: forgetting to check if file opened successfully
```cpp
ifstream fin("file.txt");
if (!fin.is_open()) {
    cerr << "Error opening file!" << endl;
    return 1;
}
```
