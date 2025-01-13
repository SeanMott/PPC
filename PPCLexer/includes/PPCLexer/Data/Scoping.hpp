#pragma once

//defines scope words for functions and objects

#include <string>

//is it a scope for global
static inline bool Subpass2_IsKeyword_Scope_Global(const char* key) { return (!strcmp(key, "global") ? true : false); }
//is it a scope for local
static inline bool Subpass2_IsKeyword_Scope_Local(const char* key) { return (!strcmp(key, "local") ? true : false); }
//is it a scope for weak
static inline bool Subpass2_IsKeyword_Scope_Weak(const char* key) { return (!strcmp(key, "weak") ? true : false); }
//is it a scope for hidden
static inline bool Subpass2_IsKeyword_Scope_Hidden(const char* key) { return (!strcmp(key, ".hidden") ? true : false); }
//is it a scope for sym
static inline bool Subpass2_IsKeyword_Scope_Sym(const char* key) { return (!strcmp(key, ".sym") ? true : false); }
