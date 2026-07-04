# GamedevUltimate

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Repository to store basic solutions as a cookbook for Unreal projects. It is created following the Ultimate Unreal C++ program created by GameDev.tv

## Prerequisites

- Unreal Engine 5.8
- JetBrains Rider
- Windows (paths below assume default UE install location)

## Commands

### Build

```bash
"C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" GamedevUltimateEditor Win64 Development "D:\Unreal\GamedevUltimate\GamedevUltimate.uproject" -NoHotReloadFromIDE
```

### Open editor

```bash
"C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe" "D:\Unreal\GamedevUltimate\GamedevUltimate.uproject"
```

### Run all tests

```bash
"C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "D:\Unreal\GamedevUltimate\GamedevUltimate.uproject" -unattended -nop4 -nosplash -NullRHI "-ExecCmds=Automation RunTests GamedevUltimate; Quit"
```

### Run a single test suite

```bash
"C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "D:\Unreal\GamedevUltimate\GamedevUltimate.uproject" -unattended -nop4 -nosplash -NullRHI "-ExecCmds=Automation RunTests GamedevUltimate.<TestSuiteName>; Quit"
```

## Repository

https://github.com/ibarkgames/gamedev-ultimate

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
