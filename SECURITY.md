# Security Policy

## Scope

`gta5-optimizer` reads and writes memory inside the GTA V process on your
own machine. It does **not** phone home, does not ship telemetry, and does
not include any network code beyond the optional local IPC socket used by
the overlay bridge.

## Supported versions

Only the latest tagged release is supported. Old builds are kept for
archival reasons and will not receive fixes.

## Reporting a vulnerability

If you find a memory corruption, an out-of-bounds read in the signature
scanner, or a way for another local process to hijack the IPC socket,
please open a private security advisory on GitHub rather than a public
issue.

Include:
- Affected commit / tag
- Steps to reproduce
- Whether the issue can be triggered without the game running

## Out of scope

- Bans issued by Rockstar for using this in GTA Online. That is expected
  behavior and not a vulnerability.
- Requests to add anti-cheat bypass. Those PRs will be closed.