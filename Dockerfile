FROM ubuntu:18.04

ENV LANG=C.UTF-8 \
    LC_ALL=C.UTF-8 

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
            ca-certificates \
            git \
            python3 \
            python3-distutils \
            curl \ 
            && rm -rf /var/lib/apt/lists/*

RUN python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)" 

ENV PATH $PATH:/root/.platformio/penv/bin
RUN echo $PATH
