# clob

clob is a C [globbing] library that supports extended and nested globbing using [brzozowski derivative].

## Supported Pattern

### Simple Globbing

 * `*`: matches any number of any characters including none 
 * `?`: matches any single character 
 * `[abc]` / `[a-z]`: matches one character given in the bracket or range
 * `[!abc]` / `[!a-z]`: matches one character that is not given in the bracket or range

### Extended Globbing

 * `?(pattern)`: match zero or one occurence of the pattern
 * `*(pattern)`: match zero or more occurences of the pattern
 * `+(pattern)`: match one or more occurences of the pattern
 * `@(pattern)`: matches exactly one occurence of the given pattern
 * `!(pattern)`: matches anything except one of the given patterns

## Examples

 * `[a-b]`: matches `a` and `b`
 * `*([a-b])`: matches e.g. ``, `a`, `b`, `aa...`, `bb..` `abbaa...`
 * `@(+(nest)ed)`: matches e.g. `nested`, `nestnested`,`nestnestnested`
 * `?(*(a|b))`: matches ``, `a...`, `b...`, does not match `ab..`

## Usage

Add clob as submodule and use `add_subdirectory` to load the library.

```
add_subdirectory(extern/clob)

...

add_executable(hello_clob ...)
target_link_libraries(hello_clob PRIVATE clob::clob)
```

### Examples

See the `examples` directory for sample code.

To build the examples
 * [clob-cli](examples/clob_cli.c)

set the `CMake` option `CLOB_BUILD_EXAMPLES` to `true`
```bash
$ cmake -DCLOB_BUILD_EXAMPLES=true ..
```

and run it from the build directory
```bash
$ ./examples/clob-cli
usage: ./examples/clob-cli "pattern" "string"

$ ./examples/clob-cli "*b" "aaab"
```

### Debug pattern

Set the `CMake` option `CLOB_DEBUG_BRZ` to enable debug prints while matching

```bash
$ cmake -DCLOB_DEBUG_BRZ=On <path_to_src_dir>
```

## Tests

Build an run tests:
```bash
$ cmake -DBUILD_TESTING=On -DCLOB_BUILD_TESTING=On ..
$ make && ctest
```

## Known Issues

 * CPP compiler is required to build tests, since [GoogleTest] is used
 * `stdio` is used inside the library


[globbing]: https://en.wikipedia.org/wiki/Glob_(programming)
[brzozowski derivative]: https://en.wikipedia.org/wiki/Brzozowski_derivative
[GoogleTest]: https://github.com/google/googletest
