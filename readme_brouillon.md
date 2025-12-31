<div align="center">

# Hyprspace (Revived)

*Le plugin de vue d'ensemble pour Hyprland, ressuscité et modernisé pour la v0.52+.*

[![Licence: BSD-3-Clause](https://img.shields.io/badge/Licence-BSD--3--Clause-blue.svg?style=for-the-badge&logo=opensource)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Stable-2ea44f?style=for-the-badge&logo=github)](https://github.com/Sidix130/Hyprspace)
[![Hyprland](https://img.shields.io/badge/Hyprland-v0.52%2B-0052cc?style=for-the-badge&logo=archlinux)](https://github.com/hyprwm/Hyprland)

## <p>｡ ₊°༺ [Sidix130](https://github.com/Sidix130) ༻°₊ ｡</p>

### [🏛️ #Histoire](#histoire) • [✨ #Fonctionnalités](#fonctionnalités) • [⚙️ #Architecture](#architecture) • [🛠️ #Installation](#installation) • [🤝 #Crédits](#crédits)

### ![Hyprspace Demo](https://github.com/KZDKM/Hyprspace/assets/41317840/ed1a585a-30d5-4a79-a6da-8cc0713828f9)

> [!IMPORTANT]
> **Compatibility Alert**: This is a heavily modified fork designed specifically for **Hyprland v0.52 and newer**. It addresses the major API breaking changes (Aquamarine/Hyprutils) that rendered the original plugin unusable.

</div>

---

## <a name="histoire"></a>🏛️ Histoire

Hyprland v0.52 a introduit des changements massifs (Breaking Changes) dans son API interne, brisant la plupart des plugins, dont le célèbre Hyprspace. Avec le projet original apparemment inactif, ce fork a été créé pour le ramener à la vie.

Nous n'avons pas juste appliqué un patch ; nous avons reconstruit la logique cœur pour s'aligner avec l'architecture moderne de Hyprland :

1.  **Refonte API :** Migration des namespaces obsolètes `Desktop::View` vers la nouvelle structure plate `desktop/`.
2.  **Standards C++ Modernes :** Mise à jour vers C++23 pour correspondre aux exigences de Hyprland.
3.  **Réparation de l'Irréparable :** Résolution des erreurs de link complexes (`undefined symbol`) et des crashs au runtime (Segfaults) qui bloquaient la migration.

👉 **[Lire le Récit de Guerre complet (MIGRATION_JOURNEY.md)](MIGRATION_JOURNEY.md)** - Une plongée technique dans les défis de cette migration.

---

## <a name="fonctionnalités"></a>✨ Fonctionnalités

*   **Workspace Overview :** Vue d'ensemble visuelle de tous les espaces de travail avec prévisualisation en direct.
*   **Drag & Drop :** Déplacez les fenêtres d'un espace à l'autre intuitivement à la souris.
*   **Multi-Monitor :** Support transparent des configurations multi-écrans.
*   **Touch Gestures :** Swipe à 3 doigts pour ouvrir/fermer (parfait pour les laptops).
*   **Customizable :** Options de style étendues pour matcher votre "rice".

---

## <a name="architecture"></a>⚙️ Architecture

Voici un aperçu de haut niveau de l'interaction entre Hyprspace et le moteur Hyprland :

```mermaid
sequenceDiagram
    participant User
    participant Hyprland
    participant Plugin as Hyprspace (Plugin)
    participant Widget as CHyprspaceWidget
    participant Renderer as Render Loop

    Note over Hyprland, Plugin: Initialization
    Hyprland->>Plugin: PLUGIN_INIT
    Plugin->>Hyprland: Register Dispatchers (hyprspace:toggle)
    Plugin->>Hyprland: Register Hooks (Render, Input, Config)

    Note over User, Widget: Activation
    User->>Hyprland: Press SUPER+TAB
    Hyprland->>Plugin: dispatchToggleOverview()
    Plugin->>Widget: toggle()
    
    rect rgb(30, 30, 30)
        Note right of Widget: Show Animation
        Widget->>Hyprland: Unfullscreen Windows
        Widget->>Hyprland: Hide Overlay Layers
        Widget->>Widget: Calculate Grid Layout
        Widget->>Hyprland: damageMonitor() (Request Frame)
    end

    Note over Hyprland, Renderer: Rendering Cycle
    loop Every Frame
        Hyprland->>Plugin: Render Hook
        Plugin->>Widget: draw()
        Widget->>Renderer: Draw Background/Panel
        
        loop For Each Workspace
            Widget->>Renderer: Draw Workspace Box
            loop For Each Window
                Widget->>Renderer: renderWindowStub()
                Note right of Renderer: Scales & Translates Window<br/>to fit in the grid
            end
        end
    end