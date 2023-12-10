# Arduino Multi-Tasking Kit | Usage > Components

## Class `Runnable`

Import file `App_Runnable.h`.

This is the base class for all components.

### `Runnable` methods

#### `void Runnable.setupAll()`

Prepare all components instances to be executed.

#### `void Runnable.loopAll()`

Execute all components instances.

### `Runnable` usage example

```c++
#include "App_Runnable.h"

void setup() {
  Serial.begin(9600);

  Runnable::setupAll();

  // Your setup code

  Serial.println("Ready");
}

void loop() {
  Runnable::loopAll();

  // Your loop code
}
```

## Class `Button` (component)

Import file `Component_Button.h`.

### `Button` methods

Simple button control.

#### `Button(uint8_t pin)` constructor

Create a button instance.

**Parameters**:

- `uint8_t pin` - Button pin.

**Connection diagram**:

- `{pin}` <-> `[Button]` <-> `(-)`

#### `bool Button.onClick()`

Get when the button is clicked ([long click](#bool-buttononlongclick)
or [short click](#bool-buttononshortclick)).

**Return**: `bool` - `true` if the button is clicked.

#### `bool Button.onShortClick()`

Get when the button is clicked for a short time.

**Return**: `bool` - `true` if the button is clicked.

#### `bool Button.onLongClick()`

Get when the button is clicked for a long time.

**Return**: `bool` - `true` if the button is clicked.

#### `ButtonState Button.getState()`

Get button state.

**Return**: `ButtonState` - Button state. See [`ButtonState` enum](/Component_Button.h#L10).

#### `bool Button.isPressed()`

Is the button being pressed?

**Return**: `bool` - `true` if the button is being pressed.

#### `bool Button.isReleased()`

Is the button being released?

**Return**: `bool` - `true` if the button is being released.

### `Button` usage example

```c++
#include <Component_Button.h>

Button btn(5);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();

  if (btn.onClick()) {
    // On long click or short click action
  }

  if (btn.onLongClick()) {
    // On long click action
  }

  if (btn.onShortClick()) {
    // On short click action
  }

  if (btn.isPressed()) {
    // Pressed
  } else {
    // Released
  }
}
```

## Class `LedDisplay8`

See [LedDisplay8](/Component_LedDisplay8.h) component source code.

## Class `PinInDigital`

See [PinInDigital](/Component_PinInDigital.h) component source code.

## Class `PinOutDigital`

See [PinOutDigital](/Component_PinOutDigital.h) component source code.

## Class `ShiftRegister`

See [ShiftRegister](/Component_ShiftRegister.h) component source code.
