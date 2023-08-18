# Something Sort of Grandish
Generate randomish strings from system entropy.

Only tested on Linux.

## Build dependencies
- make
- gcc

## Build, install & uninstall
```bash
make

# Global Install
sudo make install
# OR (local install)
make PREFIX=~/.local install

# Uninstall
sudo make uninstall
# OR (if you don't remember install path)
make PREFIX=$(dirname $(dirname $(command -v grandish))) uninstall
```

## Roadmap
- [X] Functionality
  - [X] Lower
  - [X] Numbers
  - [X] Symbols
  - [X] Upper
  - [X] Amount
- [ ] Helpful error messages
- [ ] Create man page
- [X] Create Makefile
