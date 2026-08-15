# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

An SDL2-based 2D RPG written in C. Tile-based field/dungeon exploration with turn-based battles, shops, equipment, magic, chests, and a save system. All game text/comments are in Japanese.

## Build

```
make          # builds ./game
make run      # builds and runs ./game
make clean    # removes ./game and all *.o
```

No test suite or linter is configured. `sld_test.c` is a standalone SDL scratch test (not part of the Makefile build, not a unit test) — ignore it unless asked about it directly.

Requires `sdl2-config`, `SDL2_ttf`, and `SDL2_image` dev packages on the host. `main.c` loads a hardcoded CJK font path (`/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc`) and PNG textures from `assets/` (relative to the working directory the binary is run from).

The game reads/writes `save.dat` in the working directory (raw binary dump — see Save system below).

## Architecture

**Single-loop, mode-flag driven, no OOP/dynamic dispatch.** `main.c` owns the SDL window/renderer, loads every texture up front, and runs one `while(running)` loop that polls SDL events and dispatches based on a small set of state variables — there is no per-screen struct or scene abstraction.

Two state-machine layers gate input handling:

1. **Location flags** (`in_town`, `in_cave`, `in_cave_b1`, `in_cave_b2`, `in_temple`, all false = overworld field): chosen manually with `if/else if` chains in `main.c` to pick which `get_X_tile()` / `handle_X_event()` pair to call for movement and tile events.
2. **`BattleMode` enum** (`battle.h`): `MODE_FIELD`, `MODE_BATTLE`, `MODE_MAGIC`, `MODE_USE_ITEM`, `MODE_STATUS`, `MODE_ITEM`, `MODE_EQUIPMENT`, `MODE_SAVE`, `MODE_SHOP` — drives both which `handle_*_input()` function runs and which `draw_*` function renders each frame.

There is no dynamic allocation of game objects and no headless/unit-testable core — gameplay logic is intertwined with SDL calls and manually threaded pointers (`Player *`, `Enemy *`, `BattleMode *`, cursor `int *`, texture `SDL_Texture **`, etc.) rather than a shared context struct, so most function signatures are long parameter lists. When adding a parameter to one of these flows, expect to thread it through `main.c` → area handler → the target function.

**Per-area modules** (`map.c`/`.h`, `cave.c`/`.h`, `cave_b1.c`/`.h`, `cave_b2.c`/`.h`, `temple.c`/`.h`) each follow the same shape: a static `char map[rows][cols]` tile grid, a `get_X_tile(x, y)` accessor, and a `handle_X_event(tile, ...)` that reacts to the tile the player steps on (random encounter, chest, NPC, warp to an adjacent area). Tile chars are defined in `tile.h` (`'W'`/`'M'` = wall, `'G'` = floor, etc.) — walkability is checked directly against `'M'`/`'W'` in `main.c`, not via a helper.

**Battle system** (`battle.c`/`.h`): `Enemy` (live combat instance) vs `EnemyData` (static per-area enemy table: `field_enemy_table`, `cave_enemy_table`, `cave_b1_enemy_table`, `cave_b2_enemy_table`, `temple_enemy_table`, all defined in `enemy.c`). Encounters call `setup_X_enemy()` (`enemy.c`) to pick/instantiate a random enemy and load its texture, then `start_X_battle()` (`battle.c`) to enter `MODE_BATTLE`. Elemental resistances (fire/ice/thunder) and status effects (frozen/burning/stunned/poisoned) live on both `Player` and `Enemy` with matching `bool` + `_timer` field pairs. `enemy_skill.c` holds enemy AI/special-attack behavior (`enemy_action`), separate from player-side `magic.c` (fire/ice/thunder spells) and `battle.c`'s physical attack/defend/item actions.

**Player/equipment**: `player.h` defines the `Player` struct (position, stats, status effects, `Inventory`, `Equipment`). `calc_player_status()` recomputes derived stats (attack/defense) from base stats + equipped gear and must be called after any equipment or level change. `equipment.c` handles shop purchases (`buy_*`) and equip/unequip toggles (`equip_*`), which flip a `bool X` (owned) / `bool X_equipped` pair per item in `Equipment`.

**Save system** (`save.c`): `save_game`/`load_game` do a raw `fwrite`/`fread` of the entire `GameState` struct (`game_state.h`) to/from `save.dat` — no versioning or field-level serialization. `GameState` bundles the `Player` plus every area's map buffer and location flags in one struct, so any change to `Player`, `Inventory`, `Equipment`, or the map dimensions changes the binary layout and invalidates existing `save.dat` files silently (fread will succeed but populate garbage, or fail its size check). `load_game` calls `calc_player_status()` after reading so derived stats stay consistent.

**Rendering** (`render.c`): all `draw_*` functions take an `SDL_Renderer *`/`TTF_Font *` plus whatever state they need; called from `main.c`'s render section using the same location/`BattleMode` flags that gate input. `message_ui.c` provides a single global message string (`show_message`/`get_message`/`update_message`) used for transient on-screen notices (e.g. chest pickups).
