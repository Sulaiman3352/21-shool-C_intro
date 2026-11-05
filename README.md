# 21 School — C Intensive

This repository collects the work I completed during the **21 School intensive**: a
22-day challenge in C that candidates go through to earn a place at the school.

Each day brought a new task to be written from scratch, reviewed and submitted on
schedule. Everything here is my own solution, kept as it was at the end of the
intensive — 16 projects in all, spanning the first day of shell and Git through to
building a database by the last.

## How the names work

Folders follow the school's own naming, `T01D01` or `P01D06`:

- **`T##`** — an individual task.
- **`P##`** — a team project, built with other participants.
- **`D##`** — the day of the intensive the task belongs to.

So `T05D08` is the fifth task, set on day 8.

## The projects

| Day | Project | What it covers |
|-----|---------|----------------|
| 01 | [T01D01](T01D01) | Shell and Git — cloning, repositories, files and directories, processes, config, branches |
| 02 | [T02D02](T02D02) | Vim, shell scripting, log analysis, resolving merge conflicts |
| 03 | [T03D03](T03D03) | First C programs — I/O, arithmetic, finding a maximum, floating-point comparison |
| 04 | [T04D04](T04D04) | Control structures, recursion, generating tables |
| 06 | [P01D06](P01D06) | **Team project** — Pong, with its own drawing code |
| 08 | [T05D08](T05D08) | Command-line arguments and pointers, data I/O, metrics, search |
| 09 | [T06D09](T06D09) | Sorting and memory, working across several arrays, cyclic shift, arbitrary-precision arithmetic |
| 10 | [T07D10](T07D10) | Dynamic memory — allocating it, not leaking it, matrix arithmetic, generating an image |
| 15 | [T09D15](T09D15) | Splitting a program into modules, Makefiles, static and dynamic libraries |
| 16 | [T10D16](T10D16) | Reimplementing `string.h` from scratch — `strlen`, `strcmp`, `strcpy`, `strcat`, `strchr`, `strstr`, `strtok` |
| 17 | [T11D17](T11D17) | Linked lists and stacks, with tests |
| 18 | [T12D18](T12D18) | Binary search trees — building one, three ways of traversing it, a print module |
| 20 | [P03D20](P03D20) | **Team project** — plotting a `sin(x)` graph, built on a stack |
| 22 | [T13D22](T13D22) | Reading and writing files, encryption with OpenSSL, a logging module |
| 23 | [T14D23](T14D23) | Binary files — sorting, searching and clearing stored state |
| 24 | [T15D24](T15D24) | A master database with indexing |

## Inside a project

```
T13D22/
├── README.md     the task as the school set it
├── src/          my solution
├── materials/    reference notes provided for the task
├── misc/         images used by the task description
└── LICENSE
```

Some tasks also carry a `datasets/` or `code-samples/` folder where the task
supplied data or starter code.

`README.md` and `materials/` are the school's material, not mine — they are kept so
each task can still be read alongside the solution that answers it. The school
shipped them in English, Russian and Uzbek; only the English versions are kept here.

## Building

The C tasks are built with `gcc` under the flags the school required:

```sh
gcc -Wall -Werror -Wextra
```

Code follows the Google C style guide, checked with the `.clang-format` that the C
tasks carry in `materials/linters/`. Where a task has a `Makefile`, it builds from
that:

```sh
cd T13D22/src && make
```

`T13D22` additionally links OpenSSL (`-lssl -lcrypto`). Build output is written to
each task's own `build/` directory and is not tracked here.
