# Hair and Air - UE5.6 Wind Simulation Plugin

A comprehensive wind simulation plugin for Unreal Engine 5.6+ that integrates with Groom assets and the Groom Deformer Graph system.

## Features

- ✅ Real-time wind simulation with multiple wind types
- ✅ Integration with Groom Deformer Graph
- ✅ Support for MetaHuman grooms
- ✅ Directional, turbulent, and wave-based wind
- ✅ Easy-to-use components for Groom deformation
- ✅ Blueprint-compatible interface

## Installation

1. Clone or download this repository
2. Place the `HairAndAir` folder in your UE5 project's `Plugins` directory
3. Right-click your `.uproject` file and select **"Generate Visual Studio project files"**
4. Open the `.sln` in Visual Studio 2022
5. Build the solution (Ctrl+Shift+B)
6. Open UE5.6 - Plugin loads automatically!

## Quick Start

### Step 1: Create Wind Simulation
1. In UE5.6, open your level
2. Search for "Wind Simulation" in the Place Actors panel
3. Click to place the actor in your level

### Step 2: Configure Wind
In the Details panel, adjust:
- **Wind Direction**: Direction vector (default: 1, 0, 0)
- **Wind Strength**: Force magnitude (default: 10.0)
- **Wind Frequency**: Speed of wind variations (default: 1.0)
- **Wind Turbulence**: Random variation amount (default: 0.5)
- **Enable Variable Wind**: Toggle wind variations

### Step 3: Apply to Groom
1. Select an actor with a Groom Component (e.g., MetaHuman)
2. Add "Groom Deformer Component" in Details → Add Component
3. In Details, check "Enable Deformation"
4. Press Play to test!

## Blueprint Functions

```cpp
// Wind Simulation
WindSimulation->SetWindStrength(15.0f);
WindSimulation->SetWindDirection(FVector(1.0f, 0.5f, 0.0f));
FVector WindForce = WindSimulation->GetWindForce(Position);

// Groom Deformation
GroomDeformer->SetDeformationIntensity(1.5f);
GroomDeformer->BindToWindSimulation(WindSimulation);
GroomDeformer->FindAndBindWindSimulation();
bool bActive = GroomDeformer->IsDeformationActive();
```

## Supported Groom Assets

- ✅ MetaHuman Hair
- ✅ MetaHuman Beard
- ✅ Custom UE5 Groom Assets
- ✅ Any actor with GroomComponent

## System Requirements

- **Engine**: Unreal Engine 5.6+
- **Platform**: Windows 64-bit
- **Visual Studio**: 2022 Community (or Pro/Enterprise)
- **Dependencies**: HairStrandsCore, DeformerGraph, RigVM modules

## Troubleshooting

### Plugin doesn't load
- Ensure you're using **UE5.6 or later**
- Check that **Visual Studio 2022 Community** is installed
- Regenerate Visual Studio project files: Right-click `.uproject` → "Generate Visual Studio project files"

### Compilation errors
1. Delete folders: `Intermediate/` and `Binaries/`
2. Right-click `.uproject` and select **"Generate Visual Studio project files"**
3. Close Visual Studio
4. Clean solution and rebuild

### Wind not affecting grooms
- Verify the **Groom Deformer Component** is added to the actor
- Check that **Wind Simulation** actor exists in the level
- Ensure **Enable Deformation** is checked
- Check Output Log for warnings

## Project Structure

```
HairAndAir/
├── Source/
│   └── HairAndAir/
│       ├── Public/
│       │   ├── HairAndAirModule.h
│       │   ├── WindSimulation.h
│       │   ├── GroomDeformerInterface.h
│       │   └── GroomDeformerComponent.h
│       ├── Private/
│       │   ├── HairAndAirModule.cpp
│       │   ├── WindSimulation.cpp
│       │   └── GroomDeformerComponent.cpp
│       └── HairAndAir.Build.cs
├── HairAndAir.uplugin
└── README.md
```

## Future Enhancements

- [ ] Advanced Perlin noise-based wind patterns
- [ ] Wind zones with distance falloff
- [ ] Collision-based wind deflection
- [ ] Performance optimizations for large grooms
- [ ] Full Deformer Graph node integration
- [ ] Wind presets and animation

## License

This plugin is provided for educational and development purposes.

## Support

For UE5 documentation:
- [Groom System Docs](https://docs.unrealengine.com/5.6/en-US/)
- [Deformer Graph Docs](https://docs.unrealengine.com/5.6/en-US/)
- [Hair Strands Core](https://docs.unrealengine.com/5.6/en-US/)
