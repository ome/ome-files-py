FROM openmicroscopy/ome-files-cpp-u1604
MAINTAINER ome-devel@lists.openmicroscopy.org.uk

RUN pip install numpy
RUN pip install libtiff

COPY . /git/ome-files-py

WORKDIR /git/ome-files-py
RUN python setup.py install

WORKDIR /git/ome-files-py/test
RUN python all_tests.py

WORKDIR /

CMD ["/bin/bash"]
