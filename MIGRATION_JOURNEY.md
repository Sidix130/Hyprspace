---

### Fichier 2 : `MIGRATION_JOURNEY.md`
*(Traduit en anglais pour GitHub, car c'est la langue des devs Hyprland. Garde la version française pour ton blog/LinkedIn)*.

```markdown
# ⚔️ Migration Log: Hyprspace vs Hyprland v0.52+

> **Status:** Victory 🏆
> **Difficulty:** 8/10 (Nightmare Mode)
> **Context:** Abandoned project, Breaking Changes in Hyprland API.

This document traces the battle to port the **Hyprspace** plugin to **Hyprland v0.52+**. It wasn't just a simple update; it was a reconstruction on a minefield.

---


## 💥 Chapter 1: The Great Earthquake (API Break)

Hyprland v0.52 decided to clean house. Radically.
When we popped the hood, nothing matched anymore:

*   **The Header Exodus:** Everything that was in `desktop/view/` moved to `desktop/`. `LayerSurface.hpp`, `Window.hpp`... all paths were broken.
*   **Namespace Purge:** `using namespace Desktop::View;`? Gone. `Desktop::Types`? Vanished. We had to flamethrower the code to remove these obsolete references.
*   **The Missing In Action:**
    *   `ReservedArea`: KIA. Replaced by direct management via `pMonitor->m_reservedTopLeft` and `BottomRight`.
    *   `WindowRuleApplicator`: Missing. Its functions (`noBlur`, `rounding`, `nearestNeighbor`) were absorbed directly into `m_windowData` of the `CWindow` class.
    *   `PHLANIMVAR`: A vital macro for animations, deleted. We had to replace it with the new `CAnimatedVariable` class from `Hyprutils`.

## 🕵️ Chapter 2: The Version Trap (Headers vs Source)

This was the most frustrating moment.
*   **The Setup:** We had local Hyprland sources in **v0.53.0** (bleeding edge git).
*   **The Reality:** The system was running with **v0.52.2** headers.

The code looked correct when reading local `.hpp` files, but the compiler screamed because it was reading `/usr/include`. We had to force the `Makefile` to ignore our local sources and rely solely on the system truth. **Lesson learned: Always verify what you are actually compiling against.**

## 💀 Chapter 3: The Final Boss (Undefined Symbol)

Everything compiles. We launch. **Crash.**
`undefined symbol: NColorManagement::CImageDescription::from`

This was vicious. It wasn't a code error, but a **linking** error.
*   The plugin was looking for a function that didn't exist in the running Hyprland binary.
*   **The Cause:** An old version of the plugin (`Hyprspace.so`) was lingering in `~/.config/hypr/plugins/` and was being loaded instead of our freshly compiled version.
*   **The Fix:** A brutal `cp` to overwrite the old file and ensure Hyprland loaded our work.

## 🧟 Chapter 4: The Ghost in the Machine

Last scare. The plugin refused to load with a "File not found" error pointing to a folder `~/workers-cpp` that didn't even exist.
*   **Investigation:** `grep` found nothing in the configs.
*   **The Culprit:** The internal database of `hyprpm` or a hidden config that had memorized an old installation path.
*   **The Solution:** Nuclear cleaning (`hyprpm remove`, config check) and a clean restart.

---

## 🛠️ Technical Summary for Survivors

If you have to touch this code, here are the scars to watch out for:

1.  **CWindowOverridableVar** is your friend. Don't use the old `COverridableVar`.
2.  **No `surfaceLogicalBox()`**. For layer positions, tap directly into `m_realPosition` and `m_realSize`.
3.  **CBox Initialization**. No more `{pos, size}`, you must be polite and use the explicit constructor `CBox(pos, size)`.
4.  **Nestest is vital**. The `launch-lab.sh` script that launches a nested Hyprland session saved our lives. Never develop without it.

---

**Final State:** The plugin runs like clockwork. Fluid, crash-free, and ready for the future.
*Mission Accomplished.* 🚀