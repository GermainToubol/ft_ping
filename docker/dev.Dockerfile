FROM alpine:latest AS dev

RUN apk update && apk add --no-cache build-base libcap-utils bash sudo inotify-tools

WORKDIR '/sources'
