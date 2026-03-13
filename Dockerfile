FROM gcc:13 AS builder

RUN apt-get update && \
    apt-get install -y cmake git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build -j$(nproc)

FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends libstdc++6 && \
    rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/lib64/libstdc++.so.6 /usr/lib/x86_64-linux-gnu

WORKDIR /app

COPY --from=builder /app/build/AirlineProject /usr/local/bin
COPY --from=builder /app/build/AirlineProject_TUI /usr/local/bin

COPY data/ /app/data/

CMD ["AirlineProject_TUI"]