<!--
This README originates from the repository https://github.com/othneildrew/Best-README-Template.
-->

<!-- PROJECT SHIELDS -->

<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

![C/C++ CI](https://github.com/3DExtended/Dreamroam/workflows/C/C++%20CI/badge.svg?branch=master)

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]


<!-- PROJECT LOGO -->

<br />
<p align="center">
  <!--<a href="https://github.com/3DExtended/Dreamroam">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>-->

  <h3 align="center">Dreamroam - 3D Game Engine</h3>
  

  <p align="center">
    An awesome README template to jumpstart your projects!
    <br />
    <a href="https://3dextended.github.io/Dreamroam/html/"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/3DExtended/Dreamroam">View Demo</a>
    ·
    <a href="https://github.com/3DExtended/Dreamroam/issues">Report Bug</a>
    ·
    <a href="https://github.com/3DExtended/Dreamroam/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->

## Table of Contents

- [About the Project](#about-the-project)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgements](#acknowledgements)

<!-- ABOUT THE PROJECT -->

## About The Project

<!--[![Product Name Screen Shot][product-screenshot]](https://example.com)-->

There are many game engines out there: From UI-based systems like Unity or Unreal Engine to game engines using only code. However, none of these game engines provided so much flexibility as I wanted; So I created my own.

This game engine is based on Vulkan, a low-overhead computer graphics API for Windows, Linux and (with some wrappers) MacOS. Using their approach of defining rendering pipelines we are able to create powerful workflows to define your game.
Instead of focusing on a broad feature set we focus more on low end features providing the flexibility to write custom pipelines by combining the low feature set.

Here's why another game engine:

- Educational purposes: This project focuses on testability, samples and thus is a great starting point to learn about computer graphics.
- Flexibel license: I don't need money from this project. Do what you want with this game engine as long you give credit where it is due.
- KISS principle: This engine focuses on low-overhead. You should be able to create a first 3D scene in a manner of minutes.

This project is user driven. If you find yourself needing a feature, just request it. Someone might be interested in developing it for the community and I am more than happy to merge any new features (might want to check the roadmap first though :smile:).
Just give it a try or look in the samples folder for some basic examples.

### Built With

Since writing everything from scratch is not feasible when dealing with computer graphics, here is a list of used frameworks.

- [Vulkan](https://www.khronos.org/vulkan/)
- [Lava](https://www.graphics.rwth-aachen.de:9000/lava/lava)
- [Lava-Extras](https://www.graphics.rwth-aachen.de:9000/lava/lava-extras/)
- [GLM](https://github.com/g-truc/glm)
- [GLFW](https://github.com/glfw/glfw)

<!-- GETTING STARTED -->

## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.

- CMake
    This project uses CMake to build the project. Look here on how to install it: [https://cmake.org](https://cmake.org/).
- Vulkan
    This project uses Vulkan as graphics api. Look here on how to install it: [https://www.khronos.org/vulkan](https://www.khronos.org/vulkan/).
    At the time of writing, we are using Vulkan version 1.2.141.2.

### Installation

#### 1. Clone the repo (**with its submodules**)

```sh
git clone --recursive https://github.com/3DExtended/Dreamroam.git
```

- Only if you already have cloned the repository:

```sh
git submodule init
git submodule update
```

#### 2. Configure and generate using CMake

__Note:__ Please run cmake twice. This is required for compiling the shaders through the GLSL Validator.
- For Linux and MacOS:

```sh
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
make Dreamroam
```

- For Windows:

  - Using VSCode:
        I highly recommend using [CMake Tools](https://github.com/microsoft/vscode-cmake-tools).

  - Using VSStudio:
        I'd recommend using [CMake GUI](https://cmake.org/download/) and pressing Configure and Generate to generate your project files. 

<!-- USAGE EXAMPLES -->

## Usage

The engine is still under development and there is no real usage I can show you right now. As soon as we have the bare architecture, I'll show you some usage examples.

_For more examples, please refer to the [Documentation](https://example.com)_

<!-- ROADMAP -->

## Roadmap

See the [open issues](https://github.com/3DExtended/Dreamroam/issues) for a list of proposed features (and known issues).

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->

## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->

## Contact

Peter Esser - [Twitch](https://www.twitch.tv/3dextended)

Project Link: <https://github.com/3DExtended/Dreamroam>

<!-- ACKNOWLEDGEMENTS -->

## Acknowledgements

- [Choose an Open Source License](https://choosealicense.com)
- [GitHub Pages](https://pages.github.com)
- [Codacy static code analyzer](https://app.codacy.com/manual/peter.esser2/Dreamroam/dashboard)

<!-- MARKDOWN LINKS & IMAGES -->

<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/3DExtended/Dreamroam.svg?style=flat-square

[contributors-url]: https://github.com/3DExtended/Dreamroam/graphs/contributors

[forks-shield]: https://img.shields.io/github/forks/3DExtended/Dreamroam.svg?style=flat-square

[forks-url]: https://github.com/3DExtended/Dreamroam/network/members

[stars-shield]: https://img.shields.io/github/stars/3DExtended/Dreamroam.svg?style=flat-square

[stars-url]: https://github.com/3DExtended/Dreamroam/stargazers

[issues-shield]: https://img.shields.io/github/issues/3DExtended/Dreamroam.svg?style=flat-square

[issues-url]: https://github.com/3DExtended/Dreamroam/issues

[license-shield]: https://img.shields.io/github/license/3DExtended/Dreamroam.svg?style=flat-square

[license-url]: https://github.com/3DExtended/Dreamroam/blob/master/LICENSE.txt
