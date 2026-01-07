## cpplab

Learn C++ language through grammar exercises, algorithm exercises and small implementation projects.

## build

when use seastar with source, cmake with the following command:

```Shell
cmake -DCMAKE_PREFIX_PATH="$seastar_dir/build/release;$seastar_dir/build/release/_cooking/installed" -DCMAKE_MODULE_PATH="$seastar_dir/cmake" ..
```
