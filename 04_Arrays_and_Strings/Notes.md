# 📝 04 — Arrays & Strings Notes

## Array vs Vector
Use `std::vector` unless: performance-critical, fixed-size known at compile time, embedded systems (no dynamic allocation).

## String Key Methods
| Method | Description |
|--------|-------------|
| `s.length()` / `s.size()` | Number of characters |
| `s.substr(pos, len)` | Extract substring |
| `s.find(sub)` | Find substring (returns `npos` if not found) |
| `s.replace(pos, len, str)` | Replace portion |
| `s.push_back(c)` | Append character |
| `s.empty()` | Check if empty |
| `s.clear()` | Clear string |

## Common Pitfall
`string::npos` is `(size_t)-1` — a very large number.
Always compare `find()` result with `string::npos`, never with -1:
```cpp
if (s.find("hello") != string::npos) { // correct
if (s.find("hello") != -1)            { // wrong! type mismatch
```
