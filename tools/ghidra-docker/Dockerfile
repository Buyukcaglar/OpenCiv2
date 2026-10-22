FROM eclipse-temurin:21-jdk-jammy
RUN apt-get update && apt-get install -y --no-install-recommends wget unzip python3 && rm -rf /var/lib/apt/lists/*
RUN wget -q -O /tmp/g.zip https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.1.4_build/ghidra_12.1.4_PUBLIC_20260921.zip \
 && unzip -q /tmp/g.zip -d /opt && rm /tmp/g.zip && ln -s /opt/ghidra_12.1.4_PUBLIC /opt/ghidra
RUN useradd -m -u 1000 dev || true
USER 1000
WORKDIR /work
