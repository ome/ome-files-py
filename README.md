# ome-files-py
Python bindings for https://github.com/ome/ome-files-cpp

## Building

* Build the C++ libraries (`ome-common`, `ome-files`, `ome-xml`) and install them to a `PREFIX`
* Run `python setup.py build_ext -I${PREFIX}/include -L${PREFIX}/lib -R${PREFIX}/lib` followed by `python setup.py build`

Alternatively, you can use the Docker images ([CentOS 7](https://hub.docker.com/r/openmicroscopy/ome-files-py-c7), [Ubuntu 16.04](https://hub.docker.com/r/openmicroscopy/ome-files-py-u1604)).

## Examples

`dump_planes.py` is a sample script that reads an OME-TIFF file and writes one plain TIFF image for each plane in the input file. For instance, from the `examples` directory, you can run:

```
python dump_planes.py ../test/data/multi-channel-4D-series.companion.ome
```

You can also run a sample Jupyter notebook with the [ome-files-jupyter Docker image](https://hub.docker.com/r/openmicroscopy/ome-files-jupyter). See https://github.com/openmicroscopy/ome-files-jupyter-docker for instructions.
