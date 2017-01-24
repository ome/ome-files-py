# ome-files-py
Python bindings for https://github.com/ome/ome-files-cpp

## Building

* Build the C++ libraries (`ome-common`, `ome-files`, `ome-xml`) and install them to a `PREFIX`
* Run `python setup.py build_ext -I${PREFIX}/include -L${PREFIX}/lib -R${PREFIX}/lib`
