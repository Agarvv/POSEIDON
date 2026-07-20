FROM gcc:13.2.0 AS builder

WORKDIR /app

COPY Makefile .
COPY src/ ./src/
COPY include/ ./include/

RUN make

CMD ["./build/app"]   