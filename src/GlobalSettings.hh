#pragma once

#include <string>

class GlobalSettings
{
public:
  static std::string shaderFolder;
  static bool useValidation;

  static uint16_t windowWidth;
  static uint16_t windowHeight;
};
