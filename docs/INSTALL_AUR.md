# Installation via AUR

## Building from source

You can install Hyprspace on Arch Linux using the provided `PKGBUILD`:

```bash
# Clone the repository
git clone https://github.com/Sidix130/Hyprspace.git
cd Hyprspace

# Build and install with makepkg
makepkg -si
```

## Installing from AUR

Once submitted to AUR, you can install using your preferred AUR helper:

```bash
# Using yay
yay -S hyprspace-git

# Using paru
paru -S hyprspace-git
```

## Configuration

After installation, the plugin will be located at `/usr/lib/hyprland/plugins/Hyprspace.so`.

Add to your Hyprland config (`~/.config/hypr/hyprland.conf`):

```conf
# Load the plugin
plugin = /usr/lib/hyprland/plugins/Hyprspace.so

# Configure bindings
bind = SUPER, code:49, hyprspace:toggle
bind = SUPER SHIFT, code:49, hyprspace:toggle all

# Optional: Configure plugin settings
plugin {
    overview {
        panelHeight = 250
        panelBorderWidth = 2
        workspaceMargin = 12
        # ... other settings
    }
}
```

## Available Dispatchers

- `hyprspace:toggle` - Toggle workspace overview
- `hyprspace:open` - Open workspace overview
- `hyprspace:close` - Close workspace overview

Add `all` argument to affect all monitors: `hyprspace:toggle all`
