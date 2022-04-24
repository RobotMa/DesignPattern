FROM ubuntu:20.04

# LABEL about the custom image
LABEL maintainer="qianli.ma622@gmail.com"
LABEL version="0.1"
LABEL description="This is custom Docker image for g++9 compilation"

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update

RUN apt install -y ninja-build && \
    apt install -y python3-pip && \
    apt install -y cmake pip && \
    apt install -y vim && \
    pip install conan && \
    apt clean

