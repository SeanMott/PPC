#pragma once

//defines memory offsets keywords

#include <string>

//is it a memory offset keyword for sda21
static inline bool Subpass2_IsKeyword_MemoryOffset_Sda21(const char* key) { return (!strcmp(key, "sda21") ? true : false); }
//is it a memory offset keyword for l || lower bit
static inline bool Subpass2_IsKeyword_MemoryOffset_LowerBit(const char* key) { return (!strcmp(key, "l") ? true : false); }
//is it a memory offset keyword for ha || higher bit
static inline bool Subpass2_IsKeyword_MemoryOffset_HigherBit(const char* key) { return (!strcmp(key, "ha") ? true : false); }
