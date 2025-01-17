#pragma once

//defines various keywords

#include <string>

//is it a alignment keyword
static inline bool Subpass2_IsKeyword_Alignment(const char* key) { return (!strcmp(key, ".balign") ? true : false); }
