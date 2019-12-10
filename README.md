# Kaitai-for-Michael

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
$ git clone https://github.com/sheerluck/Kaitai-for-Michael.git
$ cd Kaitai-for-Michael
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j9
$ ./mkv --path ~/Videos
```
