FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

RUN apt-get -y update 

RUN apt-get install -y gcc make nano check clang-format gcovr git valgrind htop lcov g++ xdg-utils

RUN apt-get install -y libgtest-dev cmake
RUN mkdir -p $HOME/build
RUN cd $HOME/build
RUN cmake /usr/src/googletest/googletest
RUN make

RUN cd ..
RUN rm -rf build
RUN mkdir /usr/local/lib/googletest
RUN ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
RUN ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

COPY . /app
WORKDIR /app