FROM ubuntu:16.04
MAINTAINER ome-devel@lists.openmicroscopy.org.uk

RUN apt-get update && apt-get -y install \
  build-essential \
  cmake \
  git \
  libboost-all-dev \
  libxerces-c-dev \
  libxalan-c-dev \
  libgtest-dev \
  libpng16-dev \
  libtiff5-dev \
  python-pip
RUN pip install --upgrade pip
RUN pip install Genshi
RUN pip install numpy
RUN pip install libtiff

WORKDIR /git
RUN git clone --branch='master' https://github.com/ome/ome-cmake-superbuild.git
RUN git clone --branch='master' https://github.com/ome/ome-common-cpp.git
RUN git clone --branch='master' https://github.com/ome/ome-files-cpp.git
RUN git clone --branch='master' https://github.com/ome/ome-model.git

WORKDIR /build
RUN cmake \
    -DCMAKE_CXX_STANDARD=11 \
    -Dgit-dir=/git \
    -Dbuild-prerequisites=OFF \
    -Dome-superbuild_BUILD_gtest=ON \
    -Dbuild-packages=ome-files \
    /git/ome-cmake-superbuild
RUN make
RUN make install
RUN ldconfig

COPY . /git/ome-files-py

WORKDIR /git/ome-files-py
RUN python setup.py install

WORKDIR /git/ome-files-py/test
RUN python all_tests.py

WORKDIR /

CMD ["/bin/bash"]
