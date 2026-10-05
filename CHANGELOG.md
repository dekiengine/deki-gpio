# Changelog

Notable changes to `deki-gpio`. Engine and editor changes are in the
[engine changelog](https://github.com/dekiengine/deki-engine/blob/master/CHANGELOG.md).

A package's `minEngine` names the engine version it needs. Before 1.0 a
breaking change bumps the minor across the editor, the engine and every
package together, so a package with no changes of its own is still released
alongside one that has them.

## Unreleased

### Changed
- **Names follow the code style** (deki-engine/docs/codestyle): types, functions and enum values are PascalCase, constants kPascalCase, members m_PascalCase, locals and parameters camelCase. The code is formatted with clang-format 22.
- The functions the editor finds by name are PascalCase: DekiGPIORegisterComponents, DekiGPIOGetAutoComponentCount, DekiGPIOEnsureRegistered and the rest. Built against engine ABI 21; a build of this package from before does not load and is rebuilt.

### Removed
- The former names from before 0.16.0 (bare class names, and deki-gpio's
  `DekiEsp32::ESP32PinSetup`). A scene that old is upgraded with 0.17 first.

## 0.17.1

### Changed
- `minEngine` 0.17.0. Reflection ABI 20: the package must be rebuilt.

## 0.17.0

### Added
- `IDekiGPIO`: set a pin as output or input, write, read, and count edges by
  interrupt (`CountEdges` / `TakeEdges`), with `DekiGPIO::GetCurrent()` for the
  platform's implementation.
- `GpioPinSetup`: a boot step that drives one pin high or low, with an
  optional wait afterwards. It was `DekiEsp32::ESP32PinSetup` for a few days;
  scenes naming that load as this.
