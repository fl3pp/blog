---
title: MSBuild ArtifactsPath
subtitle: Setting up an out-of-source build with MSBuild and the .NET SDK
slug: artifacts-path
date: '2025-03-03'
tags:
- MSBuild
---

A really cool but not well-known feature of the .NET SDK is the `ArtifactsPath` property. It allows you to specify a single directory, into which all build artifacts from all built projects will be placed: Binaries, Intermediates, NuGet packages, etc. This is especially useful in CI/CD environments, where you might want to keep all build artifacts in a dedicated temporary directory.

## Usage

All you need to do to use the `ArtifactsPath` property is set a MSBuild variable:

```xml
<!-- Directory.Build.props -->
<Project>
  <PropertyGroup>
    <ArtifactsPath>$(MSBuildThisFileDirectory)artifacts</ArtifactsPath>
  </PropertyGroup>
</Project>
```

All build artifacts will now be placed into subfolders of the `./artifacts` directory. It is a good idea to set this property in a `Directory.Build.props` file in the root of your repository, so that it automatically applies to all projects.

## Default Paths

Setting an `ArtifactsPath` sets off an override cascade by the .NET SDK. The following table shows a simplified overview of the most important ones:

<div class="overflow-table">

| Property | Default Value |
|--|--|
| `$(BaseOutputPath)` | `$(ArtifactsPath)\bin\$(MSBuildProjectName)\` |
| `$(BaseIntermediateOutputPath)` | `$(ArtifactsPath)\obj\$(MSBuildProjectName)\` |
| `$(PublishDir)` | `$(ArtifactsPath)\publish\$(MSBuildProjectName)\$(ArtifactsPivots)\` |
| `$(OutputPath)` | `$(BaseOutputPath)$(ArtifactsPivots)\` |
| `$(IntermediateOutputPath)` | `$(BaseIntermediateOutputPath)$(ArtifactsPivots)\` |
| `$(PackageOutputPath)` | `$(ArtifactsPath)\package\$(Configuration)\` |

</div>

The `$(ArtifactsPivots)` is a placeholder for projects that feature multiple variants. At the minimum, it will contain the `$(Configuration)`, and the `_$(RuntimeIdentifier)` and `_$(TargetFramework)` suffixes if necessary (for example, if `TargetFramework`_`s`_ is configured). 

There are even more features and knobs to turn, for example, it is possible to omit the project name from the paths though the `IncludeProjectNameInArtifactsPaths` property. Most of these can be found in the `Microsoft.Common.CurrentVersion.targets` file provided by the .NET SDK. However, note that overriding these properties might lead to unexpected consequences, so I don't recommend changing these unless absolutely necessary.

## Example

Let's look at a simple example involving a `*.csproj` class library, console project, and test project:

```bash
# Setup ArtifactsPath
echo "<Project>
  <PropertyGroup>
    <ArtifactsPath>\$(MSBuildThisFileDirectory)artifacts</ArtifactsPath>
  </PropertyGroup>
</Project>" >> Directory.Build.props

# Create Projects
dotnet new classlib --name Sample.Library --output Sample.Library 
dotnet new xunit --name Sample.Tests --output Sample.Tests 
dotnet new console --name Sample.App --output Sample.App 

# Add References 
dotnet add Sample.App reference Sample.Library
dotnet add Sample.Tests reference Sample.Library

# Create Solution
dotnet new sln --name Sample
dotnet sln add Sample.Library/Sample.Library.csproj Sample.Tests/Sample.Tests.csproj Sample.App/Sample.App.csproj

# Build Solution
dotnet build Sample.sln
```

The resulting directory structure will look like this (files omitted for brevity):

```
.
├── Sample.App
├── Sample.Library
├── Sample.Tests
└── artifacts
    ├── bin
    │   ├── Sample.App
    │   │   └── debug
    │   ├── Sample.Library
    │   │   └── debug
    │   └── Sample.Tests
    │       └── debug
    └── obj
        ├── Sample.App
        │   └── debug
        │       ├── ref
        │       └── refint
        ├── Sample.Library
        │   └── debug
        │       ├── ref
        │       └── refint
        └── Sample.Tests
            └── debug
                ├── ref
                └── refint
```

The structure would, of course, look a bit different if we built the solution in release mode, published the projects, etc.
