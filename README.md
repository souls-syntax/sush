# sush — Simple User Shell

A Unix shell written in C++ from scratch. Not a wrapper around `system()` or `/bin/sh` — every stage of command processing is implemented directly: lexing, expansion, splitting, parsing, and execution.

Built as a deep dive into Unix process model and POSIX shell semantics from userspace.

---

## Architecture

Input is processed through a staged internal pipeline before any execution occurs:

```
raw input → Lexer → Expander → FSplit → Parser → Executor
```

Each stage is a separate module under `src/internal/service/`:

- **Lexer** — tokenises raw input, handles quote boundaries and operator recognition
- **Expander** — performs variable and tilde expansion on token stream
- **FSplit** — field splitting on expanded tokens
- **Parser** — constructs `CommandNode` pipeline from token stream
- **Executor** — dispatches single commands or pipelines with correct fd wiring

Commands are registered via a `CommandRegister` — builtins and external binaries go through the same dispatch path.

---

## Features

**Parsing**
- Quote parsing (single and double)
- Variable expansion
- Operator and delimiter recognition

**Execution**
- External binary execution via `fork`/`execvp` with `PATH` resolution
- Builtin commands via command register
- I/O redirection (`>`, `>>`, `<`) with proper fd save/restore on builtins
- Pipeline execution — correct `pipe`/`dup2`/`close` fd threading across N stages

**Builtins**
- `cd`, `pwd`, `echo`, `exit`, `type`, `history`

**Shell**
- REPL prompt
- Command history

---

## What's Not Here Yet

- Job control (`Ctrl-Z`, `fg`, `bg`, `SIGTSTP` handling)
- Autocomplete
- Profile/rc file sourcing
- Custom script execution

These are known gaps, not oversights. Job control in particular requires `setpgid`/`tcsetpgrp` process group management which is next on the list.

---

## Building

**Dependencies:** Linux, `g++`, `cmake`, `ninja`

```bash
chmod +x BUILD.sh
./BUILD.sh
ninja
```

---

## License

BSD-2-Clause — see `LICENSE`

---

*Part of [souls-syntax](https://github.com/souls-syntax) — low-level tools built from scratch.*
