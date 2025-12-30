# Hyprspace

**A workspace overview plugin for Hyprland v0.52+**

Hyprspace implements a workspace overview feature similar to KDE Plasma, GNOME and macOS, providing an efficient way of workspace and window management for Hyprland.

> [!IMPORTANT]
> **Hyprland v0.52+ Support**: This fork has been updated to work with Hyprland v0.52 and newer versions. The plugin has been migrated to use the new Hyprland API with proper namespace support and public accessors.

https://github.com/KZDKM/Hyprspace/assets/41317840/ed1a585a-30d5-4a79-a6da-8cc0713828f9

## ✨ Features

- **Workspace Overview**: Visual overview of all workspaces with live window previews
- **Drag & Drop**: Move windows between workspaces by dragging
- **Multi-Monitor Support**: Works seamlessly across multiple monitors
- **Touch Gestures**: Swipe gestures for opening overview and navigating
- **Highly Configurable**: Extensive styling and behavior options
- **Performance**: Hardware-accelerated rendering with minimal overhead

## 📦 Installation

### Arch Linux (AUR)

The easiest way to install on Arch Linux:

```bash
# Using yay
yay -S hyprspace-git

# Using paru
paru -S hyprspace-git
```

After installation, add to your Hyprland config:
```conf
plugin = /usr/lib/hyprland/plugins/Hyprspace.so
```

See [docs/INSTALL_AUR.md](docs/INSTALL_AUR.md) for detailed AUR installation instructions.

### Manual Build

Requirements:
- Hyprland v0.52+ headers
- gcc/g++ with C++23 support
- pkg-config
- Required libraries: pixman, libdrm, cairo, pango

```bash
git clone https://github.com/Sidix130/Hyprspace.git
cd Hyprspace
make all
```

Load the plugin:
```conf
# In your hyprland.conf
exec-once = hyprctl plugin load /path/to/Hyprspace.so
```

### Hyprpm

```bash
hyprpm add https://github.com/Sidix130/Hyprspace
hyprpm enable Hyprspace
```

### Nix

```nix
{
  inputs = {
    hyprland.url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
    Hyprspace = {
      url = "github:Sidix130/Hyprspace";
      inputs.hyprland.follows = "hyprland";
    };
  };

  # In your configuration:
  wayland.windowManager.hyprland.plugins = [
    inputs.Hyprspace.packages.${pkgs.system}.Hyprspace
  ];
}
```

##  Usage

### Opening Overview

Bind the dispatcher to a key in your `hyprland.conf`:
```conf
bind = SUPER, TAB, hyprspace:toggle
bind = SUPER SHIFT, TAB, hyprspace:toggle, all  # Toggle on all monitors
```

Or use a vertical swipe gesture (if gestures are enabled).

### Interaction

**Window Management:**
- Click on workspace to switch to it
- Click and drag a window to move it
- Drop window on another workspace to move it there
- Click on empty area in workspace view to create new workspace

**Navigation:**
- Scroll or swipe on panel to navigate through workspaces
- Use arrow keys to navigate (if enabled)

**Exiting:**
- Click without dragging to exit
- Press `ESC` (or configured exit key) to exit
- Auto-exit on workspace switch (if configured)

## ⚙️ Configuration

### Dispatchers

- `hyprspace:toggle` - Toggle workspace overview
- `hyprspace:open` - Open workspace overview  
- `hyprspace:close` - Close workspace overview
- Add `all` argument to affect all monitors: `hyprspace:toggle all`

### Styling

#### Colors
```conf
plugin:overview {
    panelColor = rgba(0, 0, 0, 0.5)
    panelBorderColor = rgba(255, 255, 255, 0.2)
    workspaceActiveBackground = rgba(0, 0, 0, 0.25)
    workspaceInactiveBackground = rgba(0, 0, 0, 0.5)
    workspaceActiveBorder = rgba(255, 255, 255, 0.3)
    workspaceInactiveBorder = rgba(255, 255, 255, 0)
    dragAlpha = 0.2
}
```

#### Layout
```conf
plugin:overview {
    panelHeight = 250
    panelBorderWidth = 2
    workspaceMargin = 12
    reservedArea = 0              # For top notch/bar
    workspaceBorderSize = 1
    centerAligned = true          # KDE/macOS style
    onBottom = false              # Panel position
}
```

#### Behavior
```conf
plugin:overview {
    autoDrag = true
    autoScroll = true
    exitOnClick = true
    switchOnDrop = false
    exitOnSwitch = false
    showNewWorkspace = true
    showEmptyWorkspace = true
    showSpecialWorkspace = false
    exitKey = Escape              # Leave empty to disable
}
```

#### Advanced
```conf
plugin:overview {
    hideBackgroundLayers = false
    hideTopLayers = false
    hideOverlayLayers = false
    hideRealLayers = true
    drawActiveWorkspace = true
    affectStrut = true
    overrideGaps = true
    gapsIn = 20
    gapsOut = 60
    overrideAnimSpeed = 0         # 0 = use default
    disableBlur = false
    disableGestures = false
    reverseSwipe = false
}
```

## 🔧 Plugin Compatibility

- ✅ [hyprsplit](https://github.com/shezdy/hyprsplit) - Explicit support
- ✅ [split-monitor-workspaces](https://github.com/Duckonaut/split-monitor-workspaces) - Explicit support
- ✅ [hyprexpo](https://github.com/hyprwm/hyprland-plugins/tree/main/hyprexpo) - Minor bugs
- ✅ Any layout plugin (except ones overriding workspace management)

## 📝 Migration from v0.51

This fork includes updates for Hyprland v0.52+ compatibility:

- **Dispatcher Names**: Changed from `overview:*` to `hyprspace:*`  
  Update your bindings: `overview:toggle` → `hyprspace:toggle`
  
- **API Changes**: Updated to use new public accessors and namespaces
- **Build System**: Improved Makefile with better header resolution

See [docs/V0.52_hyprland/](docs/V0.52_hyprland/) for migration reference files.

## 🛠️ Development

### Building from Source
```bash
make all          # Build plugin
make clean        # Clean build artifacts
```

### Creating AUR Package
```bash
makepkg -si       # Build and install locally
makepkg --printsrcinfo > .SRCINFO  # Update package metadata
```

## 📄 License

BSD 3-Clause License - See [LICENSE](LICENSE) for details.

## 🙏 Credits

- Original plugin by [KZDKM](https://github.com/KZDKM/Hyprspace)
- Hyprland v0.52+ migration by [Sidix130](https://github.com/Sidix130)
- All awesome [contributors](https://github.com/KZDKM/Hyprspace/graphs/contributors)

## 🔗 Links

- [Original Repository](https://github.com/KZDKM/Hyprspace)
- [Hyprland](https://github.com/hyprwm/Hyprland)
- [Report Issues](https://github.com/Sidix130/Hyprspace/issues)
