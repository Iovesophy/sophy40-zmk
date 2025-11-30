# sophy40-zmk

ZMK Firmware configuration for custom keyboard.

## Build

This repository uses GitHub Actions to automatically build the firmware.

1. Push changes to GitHub
2. Check build progress in the Actions tab
3. Download firmware (.uf2 files) from Artifacts when build completes

## Flashing Firmware

1. Put keyboard into reset mode (double-tap RESET button)
2. Device will appear as mass storage device
3. Drag and drop the downloaded .uf2 file
4. Device will automatically reboot

## Customizing Keymap

Edit the `config/corne.keymap` file to customize your keymap.

### Layer Structure

- **Layer 0 (Default)**: Basic QWERTY layout
- **Layer 1 (Lower)**: Numbers, arrow keys, Bluetooth controls
- **Layer 2 (Raise)**: Symbol keys

## Configuration Files

- `config/corne.keymap`: Keymap definitions
- `config/corne.conf`: Keyboard settings (Bluetooth, sleep, etc.)
- `config/west.yml`: ZMK version management

## Supported Boards

Current configuration supports:
- nice!nano v2

To use a different board, modify the `-b` option in `.github/workflows/build.yml`.

## References

- [ZMK Documentation](https://zmk.dev/)
- [ZMK Keycodes](https://zmk.dev/docs/codes)
- [ZMK Behaviors](https://zmk.dev/docs/behaviors)
