FROM debian:latest AS reference-base

RUN apt update && apt install iproute2 -y

FROM reference-base AS ip
RUN apt install iputils-ping -y

FROM reference-base AS inet
RUN apt install inetutils-ping -y
