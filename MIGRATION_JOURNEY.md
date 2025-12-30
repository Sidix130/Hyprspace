# ⚔️ Récit de Migration : Hyprspace vs Hyprland v0.52+

> **Statut :** Victoire 🏆
> **Difficulté :** 8/10 (Mode Cauchemar)
> **Contexte :** Projet abandonné par le créateur, API Hyprland en rupture totale.

Ce document retrace la bataille pour porter le plugin **Hyprspace** sur **Hyprland v0.52+**. Ce n'était pas une simple mise à jour, c'était une reconstruction sur un terrain miné.

---

## 💥 Chapitre 1 : Le Grand Tremblement de Terre (API Break)

Hyprland v0.52 a décidé de faire le ménage. Radicalement.
Quand on a ouvert le capot, plus rien ne correspondait :

*   **L'Exode des Headers :** Tout ce qui était dans `desktop/view/` a déménagé dans `desktop/`. `LayerSurface.hpp`, `Window.hpp`... tous les chemins étaient cassés.
*   **La Purge des Namespaces :** `using namespace Desktop::View;` ? Disparu. `Desktop::Types` ? Envolé. Il a fallu nettoyer le code au lance-flammes pour retirer ces références obsolètes.
*   **Les Disparus :**
    *   `ReservedArea` : Mort au combat. Remplacé par une gestion directe via `pMonitor->m_reservedTopLeft` et `BottomRight`.
    *   `WindowRuleApplicator` : Porté disparu. Ses fonctions (`noBlur`, `rounding`, `nearestNeighbor`) ont été absorbées directement dans `m_windowData` de la classe `CWindow`.
    *   `PHLANIMVAR` : Une macro vitale pour les animations, supprimée. On a dû la remplacer par la nouvelle classe `CAnimatedVariable` de `Hyprutils`.

## 🕵️ Chapitre 2 : Le Piège des Versions (Headers vs Source)

C'était le moment le plus frustrant.
*   **Le setup :** On avait les sources locales de Hyprland en **v0.53.0** (la pointe).
*   **La réalité :** Le système tournait avec les headers de la **v0.52.2**.

Le code semblait correct quand on lisait les fichiers `.hpp` locaux, mais le compilateur nous insultait parce qu'il lisait les fichiers de `/usr/include`. On a dû forcer le `Makefile` à ignorer nos sources locales pour se fier uniquement à la vérité du système. **Leçon apprise : Toujours vérifier contre quoi on compile vraiment.**

## 💀 Chapitre 3 : Le Boss de Fin (Undefined Symbol)

Tout compile. On lance. **Crash.**
`undefined symbol: NColorManagement::CImageDescription::from`

C'était vicieux. Ce n'était pas une erreur de code, mais une erreur de **linkage**.
*   Le plugin cherchait une fonction qui n'existait pas dans le binaire Hyprland en cours d'exécution.
*   **La cause :** Une vieille version du plugin (`Hyprspace.so`) traînait dans `~/.config/hypr/plugins/` et était chargée à la place de notre nouvelle version fraîchement compilée.
*   **Le fix :** Un `cp` brutal pour écraser l'ancien fichier et s'assurer que Hyprland chargeait bien notre travail.

## 🧟 Chapitre 4 : Le Fantôme dans la Machine

Dernière frayeur. Le plugin refusait de se charger avec une erreur "Fichier introuvable" pointant vers un dossier `~/workers-cpp` qui n'existait même pas.
*   **L'enquête :** `grep` ne trouvait rien dans les configs.
*   **Le coupable :** La base de données interne de `hyprpm` ou une config cachée qui avait mémorisé un ancien chemin d'installation.
*   **La solution :** Nettoyage par le vide (`hyprpm remove`, vérification des configs) et relance propre.

---

## 🛠️ Résumé Technique pour les Survivants

Si vous devez toucher à ce code, voici les cicatrices à surveiller :

1.  **CWindowOverridableVar** est votre ami. N'utilisez plus l'ancien `COverridableVar`.
2.  **Pas de `surfaceLogicalBox()`**. Pour la position des layers, tapez directement dans `m_realPosition` et `m_realSize`.
3.  **Initialisation CBox**. Plus de `{pos, size}`, il faut être poli et utiliser le constructeur `CBox(pos, size)`.
4.  **Nestest est vital**. Le script `launch-lab.sh` qui lance une session Hyprland imbriquée nous a sauvé la vie. Ne développez jamais sans ça.

---

**État Final :** Le plugin tourne comme une horloge. Fluide, sans crash, et prêt pour le futur.
*Mission accomplie.* 🚀
