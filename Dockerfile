# Use uma imagem base do Ubuntu
FROM ubuntu:20.04

# Atualize e instale as dependências necessárias
RUN apt-get update && \
    apt-get install -y gcc make

# Copie o código-fonte para o contêiner
COPY . /app

# Defina o diretório de trabalho
WORKDIR /app

# Compile o código-fonte
RUN gcc dns_server.c -o dns_server

# Comando para executar o servidor DNS
CMD ["./dns_server"]
