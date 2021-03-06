# Toy Cpp Project with Kaitai

![Image](<https://i.imgur.com/NYpxwwX.png>)

```
$ kaitai-struct-compiler-0.9-SNAPSHOT/bin/kaitai-struct-compiler \
  --target cpp_stl --cpp-standard 11 --ksc-exceptions            \
  ksy/generated.ksy

$ kaitai-struct-compiler-0.9-SNAPSHOT/bin/kaitai-struct-compiler     \
  --target cpp_stl --cpp-standard 11 --no-auto-read --ksc-exceptions \
  ksy/generated.ksy
```


```
$ git clone https://github.com/kaitai-io/kaitai_struct_cpp_stl_runtime
```

```
# apt install build-essential
# apt install git
# apt install cmake
# apt install libfmt-dev   # or https://fmt.dev/latest/usage.html#building-the-library

```


```
$ git clone https://github.com/sheerluck/Toy-Cpp-Project-with-Kaitai.git
$ cd Toy-Cpp-Project-with-Kaitai
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
$ make -j9
$ ./mkv --path ~/Videos
$ clang-tidy -checks=*,-fuchsia-default-arguments-declarations,
                       -fuchsia-default-arguments-calls,
                       -readability-braces-around-statements,
                       -hicpp-braces-around-statements,
                       -google-readability-braces-around-statements,
                       -modernize-use-trailing-return-type
                       -p ./ ../main.cpp 
```
