# clang-format Base Style Selection Rationale

## Executive Summary

This document explains why **LLVM** was selected as the base style for our `.clang-format` configuration and evaluates the alternative options that were considered.

## Background

`clang-format` provides several predefined base styles that serve as starting points for code formatting. Each base style reflects the coding conventions of major software projects and organizations. Choosing the right base style is important because it:

- Establishes consistent formatting across the codebase
- Reduces configuration overhead by providing sensible defaults
- Aligns with industry best practices
- Facilitates onboarding of new developers familiar with the style

## Available Base Style Options

### 1. LLVM ✅ (Selected)

**Origin**: LLVM Compiler Infrastructure Project

**Key Characteristics**:
- **Indentation**: 2 spaces
- **Column Limit**: 80 characters (customizable)
- **Brace Style**: Attached (opening brace on same line)
- **Pointer Alignment**: Left (`int* ptr`)
- **Philosophy**: Compact, readable, modern C++ focused

**Strengths**:
- Industry-standard for high-performance C++ projects
- Excellent defaults for modern C++ (C++11 and beyond)
- Compact formatting without sacrificing readability
- Well-maintained and actively used by major projects
- Balanced approach between vertical and horizontal space usage
- Strong community adoption in systems programming

**Weaknesses**:
- 80-column default may feel restrictive (easily customizable)
- Less opinionated than Google style (requires more customization)

**Example Code**:
```cpp
class MyClass {
public:
  void myFunction(int* ptr) {
    if (condition) {
      doSomething();
    }
  }
};
```

---

### 2. Google

**Origin**: Google C++ Style Guide

**Key Characteristics**:
- **Indentation**: 2 spaces
- **Column Limit**: 80 characters
- **Brace Style**: Attached
- **Pointer Alignment**: Left
- **Philosophy**: Highly opinionated, readability-focused

**Strengths**:
- Extremely well-documented style guide
- Optimized for large codebases with many contributors
- Strong emphasis on readability
- Widely recognized in industry

**Weaknesses**:
- Very opinionated (may conflict with existing conventions)
- Some rules designed specifically for Google's infrastructure
- More restrictive than LLVM
- Includes non-formatting conventions (naming, etc.) that may not apply

**Why Not Selected**:
- Too restrictive for our project's needs
- LLVM provides similar benefits with more flexibility
- Google style is optimized for Google's specific ecosystem

---

### 3. Chromium

**Origin**: Chromium Browser Project

**Key Characteristics**:
- **Indentation**: 2 spaces
- **Column Limit**: 80 characters
- **Brace Style**: Attached
- **Philosophy**: Derivative of Google style with browser-specific tweaks

**Strengths**:
- Well-suited for large browser-related projects
- Similar benefits to Google style

**Weaknesses**:
- Tailored specifically for Chromium's needs
- Less general-purpose than LLVM

**Why Not Selected**:
- Project-specific optimizations not relevant to our codebase
- LLVM provides better general-purpose defaults

---

### 4. Mozilla

**Origin**: Mozilla Firefox Project

**Key Characteristics**:
- **Indentation**: 2 spaces
- **Column Limit**: 80 characters
- **Brace Style**: Mixed (different rules for different contexts)
- **Philosophy**: Mozilla-specific conventions

**Strengths**:
- Well-established in Mozilla ecosystem

**Weaknesses**:
- Highly specific to Mozilla's codebase
- Less widely adopted outside Mozilla
- More complex brace placement rules

**Why Not Selected**:
- Too specific to Mozilla's ecosystem
- Less industry recognition than LLVM

---

### 5. WebKit

**Origin**: WebKit Browser Engine

**Key Characteristics**:
- **Indentation**: 4 spaces
- **Column Limit**: None (or very high)
- **Brace Style**: Attached
- **Philosophy**: More spacious, traditional C++ style

**Strengths**:
- More vertical spacing for readability
- Traditional feel

**Weaknesses**:
- 4-space indentation increases horizontal scrolling
- Less compact than modern styles
- Specific to WebKit ecosystem

**Why Not Selected**:
- 4-space indentation wastes horizontal space
- Less modern approach than LLVM
- Not widely adopted outside WebKit

---

### 6. Microsoft

**Origin**: Microsoft Coding Conventions

**Key Characteristics**:
- **Indentation**: 4 spaces
- **Column Limit**: None
- **Brace Style**: Allman (braces on new lines)
- **Philosophy**: Traditional Windows/C# influenced style

**Strengths**:
- Familiar to Windows developers
- Very readable with vertical spacing

**Weaknesses**:
- Allman brace style wastes vertical space
- 4-space indentation increases line length
- Less common in modern C++ projects
- More influenced by C# conventions

**Example Code**:
```cpp
class MyClass
{
public:
    void myFunction(int* ptr)
    {
        if (condition)
        {
            doSomething();
        }
    }
};
```

**Why Not Selected**:
- Excessive vertical spacing reduces code density
- Allman braces not preferred for modern C++
- Less adoption in systems programming community

---

### 7. GNU

**Origin**: GNU Project Coding Standards

**Key Characteristics**:
- **Indentation**: 2 spaces
- **Column Limit**: 79 characters
- **Brace Style**: Highly distinctive (braces indented)
- **Philosophy**: GNU-specific, very traditional

**Example Code**:
```cpp
class MyClass
  {
public:
    void myFunction (int* ptr)
      {
        if (condition)
          {
            doSomething ();
          }
      }
  };
```

**Strengths**:
- Well-established in GNU ecosystem

**Weaknesses**:
- Unusual brace placement confusing to most developers
- Spaces before parentheses in function calls
- Very limited adoption outside GNU projects
- Considered outdated by modern standards

**Why Not Selected**:
- Highly unconventional formatting
- Poor readability for most developers
- Virtually no adoption in modern C++ projects

---

## Decision: LLVM Selected

### Primary Reasons

1. **Modern C++ Focus**
   - LLVM style is designed for modern C++ codebases (C++11+)
   - Our project uses C++17 (as specified in `.clang-format`)
   - Excellent support for modern language features

2. **Industry Standard**
   - Widely adopted in high-performance C++ projects
   - Used by LLVM, Clang, Rust compiler, and many other major projects
   - Familiar to experienced C++ developers

3. **Balanced Approach**
   - Compact without being cramped (2-space indentation)
   - Readable without excessive vertical spacing
   - Good defaults that work well with customization

4. **Flexibility**
   - Less opinionated than Google style
   - Easy to customize for project-specific needs
   - Provides solid foundation without forcing unnecessary conventions

5. **Pointer/Reference Alignment**
   - Left-aligned pointers (`int* ptr`) match our preference
   - Prevents misleading declarations like `int* a, b` (where `b` is not a pointer)

6. **Brace Style**
   - Attached braces save vertical space
   - Consistent with modern C++ conventions
   - Matches our existing codebase style

### Customizations Applied

Our `.clang-format` builds on LLVM with project-specific enhancements:

| Setting | LLVM Default | Our Value | Reason |
|---------|--------------|-----------|--------|
| `ColumnLimit` | 80 | 100 | Modern displays support wider lines |
| `InsertBraces` | N/A | `true` | Prevents dangling else bugs |
| `AllowShortIfStatementsOnASingleLine` | `WithoutElse` | `Never` | Consistency and safety |
| `AllowShortFunctionsOnASingleLine` | `All` | `None` | Debugging and readability |
| `IncludeBlocks` | `Preserve` | `Regroup` | Organized header structure |

These customizations enhance safety, readability, and maintainability while preserving LLVM's core philosophy.

## Comparison Matrix

| Feature | LLVM ✅ | Google | Microsoft | WebKit | GNU |
|---------|---------|--------|-----------|--------|-----|
| Indentation | 2 spaces | 2 spaces | 4 spaces | 4 spaces | 2 spaces |
| Brace Style | Attached | Attached | Allman | Attached | Indented |
| Column Limit | 80 | 80 | None | None | 79 |
| Modern C++ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ |
| Flexibility | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ |
| Industry Adoption | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ | ⭐ |
| Code Density | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐ | ⭐⭐ | ⭐⭐ |
| Readability | ⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ |

## Conclusion

**LLVM** was selected as the base style because it provides:
- The best foundation for modern C++ development
- Industry-standard formatting familiar to experienced developers
- Excellent balance between compactness and readability
- Flexibility to customize for project-specific needs
- Strong alignment with our existing code conventions

While other styles like **Google** and **Microsoft** have merit in their respective ecosystems, **LLVM** offers the optimal combination of modern C++ support, industry adoption, and customization flexibility for our project.

## References

- [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html)
- [clang-format Documentation](https://clang.llvm.org/docs/ClangFormat.html)
- [clang-format Style Options](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

---

**Document Version**: 1.0  
**Last Updated**: 2025-12-11  
**Author**: Astra Development Team
