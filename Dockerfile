FROM ubuntu:22.04 as base_image

# dev tools and python
RUN apt update && \
    apt install -y build-essential gcc ninja-build git cmake && \
    apt install -y python3.10 python3-pip && \
    apt -y clean all && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /root/.cache/

# installing C++ deps
# eigen is a fast linear algebra library
# https://github.com/fmtlib/fmt/issues/2157
FROM base_image as cpp_installer
RUN mkdir /dependencies/
RUN git clone https://gitlab.com/libeigen/eigen.git /dependencies/eigen && \
    mv /dependencies/eigen/Eigen/ /usr/include/
RUN git clone https://github.com/fmtlib/fmt.git /dependencies/fmt && \
    cd /dependencies/fmt && mkdir build && cd build && cmake .. && \
    make && make test && make install

# install python packages using multistage build
FROM base_image as pip_installer
COPY requirements.txt .
RUN pip3 install --user -r requirements.txt

# move everything over and setup dev environment
FROM base_image
COPY --from=pip_installer /root/.local /root/.local
COPY --from=cpp_installer /usr/ /usr/
RUN mkdir engine_nnue
WORKDIR /engine_nnue
