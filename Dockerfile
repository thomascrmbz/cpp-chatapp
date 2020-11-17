FROM madduci/docker-alpine-cpp:gcc-6

WORKDIR /chatapp/

COPY . .

RUN make clean all HTTP_LIB=/chatapp/.lib/cpp-http-server WEBSOCKET_LIB=/chatapp/.lib/cpp-websocket

FROM alpine:3.12.0 AS client
WORKDIR /chatapp/
COPY --from=0 /chatapp/client.out .

RUN apk update && apk add --no-cache \ 
    libstdc++

EXPOSE 3000

ENTRYPOINT [ "./client.out" ]

FROM alpine:3.12.0 AS server
WORKDIR /chatapp/
COPY --from=0 /chatapp/server.out .

RUN apk update && apk add --no-cache \ 
    libstdc++

EXPOSE 3000

ENTRYPOINT [ "./server.out" ]