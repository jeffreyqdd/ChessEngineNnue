FROM ubuntu:22.04 as base_image

# dev tools and python
RUN apt update && \
    apt install -y build-essential gcc ninja-build git && \
    apt install -y python3.10 python3-pip && \
    apt -y clean all && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /root/.cache/

# installing C++ deps
# eigen is a fast linear algebra library and catch2 is a unittest framework
FROM base_image as cpp_installer
RUN mkdir /dependencies/
RUN git clone https://gitlab.com/libeigen/eigen.git /dependencies/eigen
RUN git clone https://github.com/catchorg/Catch2.git /dependencies/Catch2
RUN mv /dependencies/eigen/Eigen/ /usr/include/
RUN mkdir /usr/include/Catch2 && \
    mv /dependencies/Catch2/extras/catch_amalgamated.* /usr/include/Catch2/

# install python packages using multistage build
FROM base_image as pip_installer
COPY requirements.txt .
RUN pip3 install --user -r requirements.txt

# move everything over and setup dev environment
FROM base_image
COPY --from=pip_installer /root/.local /root/.local
COPY --from=cpp_installer /usr/include/Eigen/ /usr/include/Eigen/
COPY --from=cpp_installer /usr/include/Catch2/ /usr/include/Catch2
RUN mkdir engine_nnue
