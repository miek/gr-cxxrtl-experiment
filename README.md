This is an experiment in running cxxrtl simulation inside a GNURadio flowgraph block. This won't be maintained any further and is just here for reference as some people were interested, but it should reappear in some more usable form in the future.

Note: if using this for reference, expect the method for getting/setting simulation values to change upstream in the near future.

Build:

```
python3 fmdemod.py
mkdir build
cd build
cmake ..
make
make install
```

There's an example flowgraph in `examples/`.
