#pragma once

#include <hyprutils/animation/AnimatedVariable.hpp>

#include "Color.hpp"
#include "../defines.hpp"
#include "../desktop/DesktopTypes.hpp"

enum eAVarDamagePolicy : int8_t {
    AVARDAMAGE_NONE   = -1,
    AVARDAMAGE_ENTIRE = 0,
    AVARDAMAGE_BORDER,
    AVARDAMAGE_SHADOW
};

enum eAnimatedVarType : int8_t {
    AVARTYPE_INVALID = -1,
    AVARTYPE_FLOAT,
    AVARTYPE_VECTOR,
    AVARTYPE_COLOR
};

// Utility to bind a type with its corresponding eAnimatedVarType
template <class T>
// NOLINTNEXTLINE(readability-identifier-naming)
struct STypeToAnimatedVarType_t {
    static constexpr eAnimatedVarType value = AVARTYPE_INVALID;
};

template <>
struct STypeToAnimatedVarType_t<float> {
    static constexpr eAnimatedVarType value = AVARTYPE_FLOAT;
};

template <>
struct STypeToAnimatedVarType_t<Vector2D> {
    static constexpr eAnimatedVarType value = AVARTYPE_VECTOR;
};

template <>
struct STypeToAnimatedVarType_t<CHyprColor> {
    static constexpr eAnimatedVarType value = AVARTYPE_COLOR;
};

template <class T>
inline constexpr eAnimatedVarType typeToeAnimatedVarType = STypeToAnimatedVarType_t<T>::value;

// Utility to define a concept as a list of possible type
template <class T, class... U>
concept OneOf = (... or std::same_as<T, U>);

// Concept to describe which type can be placed into CAnimatedVariable
// This is mainly to get better errors if we put a type that's not supported
// Otherwise template errors are ugly
template <class T>
concept Animable = OneOf<T, Vector2D, float, CHyprColor>;

struct SAnimationContext {
    PHLWINDOWREF      pWindow;
    PHLWORKSPACEREF   pWorkspace;
    PHLLSREF          pLayer;

    eAVarDamagePolicy eDamagePolicy = AVARDAMAGE_NONE;
};

template <Animable VarType>
using CAnimatedVariable = Hyprutils::Animation::CGenericAnimatedVariable<VarType, SAnimationContext>;

template <Animable VarType>
using PHLANIMVAR = UP<CAnimatedVariable<VarType>>;

template <Animable VarType>
using PHLANIMVARREF = WP<CAnimatedVariable<VarType>>;
#pragma once
#include <hyprland/src/Compositor.hpp>
#include <hyprutils/animation/AnimationConfig.hpp>

class CHyprspaceWidget {

    bool active = false;

    int64_t ownerID;

    // animation override stuff
    Hyprutils::Animation::SAnimationPropertyConfig curAnimationConfig;
    Hyprutils::Animation::SAnimationPropertyConfig curAnimation;

    // for checking mouse hover for workspace drag and move
    // modified on draw call, accessed on mouse click and release
    std::vector<std::tuple<int, CBox>> workspaceBoxes;

    // for storing the fullscreen state of windows prior to overview activation (which unfullscreens all windows)
    std::vector<std::tuple<uint32_t, eFullscreenMode>> prevFullscreen;

    // for storing the layer alpha values prior to overview activation (which sets all panel to transparent when configured)
    std::vector<std::tuple<PHLLS, float>> oLayerAlpha;

    // for click-to-exit
    std::chrono::system_clock::time_point lastPressedTime = std::chrono::high_resolution_clock::now();

    bool swiping = false;
    // whether if the panel is active before the current swiping event
    bool activeBeforeSwipe = false;
    double avgSwipeSpeed = 0.;
    // number of swiping speed frames recorded
    int swipePoints = 0;
    // on second thought, this seems redundant as we could just write to curYOffset while swiping
    double curSwipeOffset = 10.;

    PHLANIMVAR<float> workspaceScrollOffset;

public:

    // for slide-in animation and swiping
    PHLANIMVAR<float> curYOffset;

    CHyprspaceWidget(uint64_t);
    ~CHyprspaceWidget();

    PHLMONITOR getOwner();
    bool isActive();

    void show();
    void hide();

    void updateConfig();

    // should be called active or not
    void draw();

    // reserves area on owner monitor
    void updateLayout();

    bool buttonEvent(bool, Vector2D coords);
    bool axisEvent(double, Vector2D coords);

    bool isSwiping();

    bool beginSwipe(IPointer::SSwipeBeginEvent);
    bool updateSwipe(IPointer::SSwipeUpdateEvent);
    bool endSwipe(IPointer::SSwipeEndEvent);

};
