# Contributing to gta5-optimizer

Thanks for wanting to help out. This project is a hobbyist-oriented
tuning and overlay toolkit for GTA V on Windows. It is not affiliated
with Rockstar Games or Take-Two Interactive.

## Ground rules

- Use it only in **single player / invite-only sessions**. Do not bring
  the memory-editing or overlay features into GTA Online. Rockstar's
  anti-cheat will ban you and we will not help you evade it.
- Keep PRs focused. One feature or fix per PR.
- Match the existing folder layout: `src/handlers` are thin, `src/services`
  hold logic, `src/adapters` wrap OS/driver calls.
- No hardcoded offsets. All game signatures live in `config/signatures.ini`
  and get resolved at runtime by `src/services/signature_service.cpp`.
- No obfuscated code. If you need to hide something from review, it doesn't
  belong here.

## Building

```
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

The C# overlay companion (`companion/overlay-bridge`) targets .NET 8
and is built separately with `dotnet build`.

## Code style

- C++20, 4-space indent, `snake_case` for functions and files.
- `PascalCase` for types.
- Prefer `std::` over Win32 types unless you're in an adapter.
- Log through `utils/logger.hpp`, never `printf`.

## Reporting bugs

Open an issue with the log from `logs/optimizer-YYYYMMDD.log`, your GPU
driver version, and the exact game build number shown in the overlay.